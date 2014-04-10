/**
 * A pintool that calculates the call rate of each function in an executable
 *
 * File: callrate.cpp
 *
 */



/*******************************
 * Dependencies
 *******************************/

#include "pin++/Image_Instrument.h"
#include "pin++/Pintool.h"
#include "pin++/Symbol.h"
#include "pin++/Section.h"
#include "pin++/Buffer.h"
#include "pin++/Callback.h"

#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include <hash_map>



/*******************************
 * Callback
 *******************************/

/**
 * Callback class that processes function calls and calculate call rate.
 */
class Call_Rate : public OASIS::Pin::Callback <Call_Rate (void)>
{
public:
  /**
   * Constructor.
   */
  Call_Rate (void)
    : rtn_name_ (),
      rtn_count_ (0)
  {

  }

  /**
   * Call back analysis routine.
   */
  void handle_analyze (void)
  {
    ++this->rtn_count_;
  }

  /**
   * Getter for the routine name.
   *
   * @return      returns the name of the routine
   */
  std::string rtn_name (void) const
  {
    return this->rtn_name_;
  }

  /**
   * Setter for the routine name.
   */
  void rtn_register (std::string rtn_name)
  {
    this->rtn_name_ = rtn_name;
  }

  /**
   * Getter the routine count.
   *
   * @return      returns the count of the routine.
   */
  UINT64 count (void) const
  {
    return this->rtn_count_;
  }

private:  
  std::string rtn_name_;      // routine name
  UINT64 rtn_count_;          // routine count
};



/*******************************
 * Instrument
 *******************************/

/**
 * Image level instrument class.
 */
class Image : public OASIS::Pin::Image_Instrument <Image>
{
public:
  /**
   * Instrument routine.
   */
  void handle_instrument (const OASIS::Pin::Image & img)
  {
    // first iteration
    // count total number of routines in the image
    UINT64 total_rtn_in_img = 0;
    for (auto sec : img)
    {
      for (auto rtn : sec)
      {
        ++total_rtn_in_img;
      }
    }
    
    // second iteration
    // pre-allocate one buffer for each image
    // the buffer size is equal to the number of routines in the image
    item_type item ((size_t) total_rtn_in_img);
    item_type::iterator callback = item.begin ();
    
    for (auto sec : img)
    {
      for (auto rtn : sec)
      {
        // guard automatically open and close the rtn for rtn_iter
        OASIS::Pin::Routine_Guard guard (rtn);
        callback->rtn_register (OASIS::Pin::Symbol::undecorate (rtn.name (), UNDECORATION_NAME_ONLY));
        rtn.insert_call (IPOINT_BEFORE, callback);
        ++callback;
      }
    }
    
    // the buffer list contains one buffer for each image
    this->rtn_buffer_list_.push_back (item);
  }

  /**
   * Calculate the total number of routine calls from all the images
   *
   * @return    total number of routine calls
   */
  UINT64 total_count (void) const
  {
    UINT64 total_rtn_count = 0;

    for (auto buffer : this->rtn_buffer_list_)
    {
      for (auto item : buffer)
      {
        total_rtn_count += item.count ();
      }
    }

    return total_rtn_count;
  }

  /**
   * Generate an output of function call rate into a file by sorting.
   * The output format is: <routine name> : <routine call counts>, <total routine calls>, <callrate>
   *
   * Each routine - count pair is pushed into a vector; the vector is sorted,
   * and the counts for the same routine are combined for output.
   *
   * @param[in]    output_file    the file pointer for output
   */
  void output_to_file_by_sorting (std::ofstream & fout)
  {
    UINT64 total_rtn_count = this->total_count ();

    // a vector of string - UINT64 pair
    typedef std::vector<std::pair<std::string, UINT64>> pair_vector;
    pair_vector pair_list;

    // iterate through the buffer and put the result into the vector
    for (auto buffer : this->rtn_buffer_list_)
    {
      for (auto item : buffer)
      {
        if (item.count () > 0)
        {
          pair_list.push_back (std::make_pair (item.rtn_name (), item.count ()));          
        }
      }
    }
    
    // sort the vector so that the counts for the same routine can be combined
    std::sort (pair_list.begin (), pair_list.end ());
    size_t len = pair_list.size ();

    // combine the count for the same routine and output the result to fout
    for (size_t i = 0; i < len; ++i)
    {
      std::string rtn_name = pair_list.at (i).first;
      UINT64 rtn_count = pair_list.at (i).second;
      while (i+1 < len && pair_list.at (i+1).first == rtn_name)
      {
        ++i;
        rtn_count += pair_list.at (i).second;
      }
      double call_rate = double (rtn_count) / double (total_rtn_count);
      fout << rtn_name << " : " << rtn_count << ", " << total_rtn_count << ", " << call_rate << std::endl;
    }
  }

  /**
   * Generate an output of function call rate into a file by hashing.
   * The output format is: <routine name> : <callrate as double>.
   *
   * Each routine - count is pushed into a hashmap. This hashmap is traversed for output.
   *
   * @param[in]    output_file    the file pointer for output
   */
  void output_to_file_by_hashmap (std::ofstream & fout)
  {
    UINT64 total_rtn_count = 0;

    // a hashmap of string - UINT64
    stdext::hash_map<std::string, UINT64> map;

    std::string curr_name = "";
    UINT64 curr_count = 0;

    // iterate through the buffer and put the result into the hashmap
    for (auto buffer : this->rtn_buffer_list_)
    {
      for (auto item : buffer)
      {
        curr_count = item.count ();

        if (curr_count > 0)
        {
          curr_name = item.rtn_name ();

          if ( map.count (curr_name) == 1 )
          {
            // routine already in the map, update the count
            stdext::hash_map<std::string, UINT64>::iterator it = map.find (curr_name);
            map[curr_name] = it->second + curr_count;            
          }
          else
          {
            // routine not found in the map
            map[curr_name] = curr_count;
          }
          
          total_rtn_count = total_rtn_count + curr_count;
        }

      }
    }
    
    double call_rate = 0.0;

    for (auto item : map)
    {
      call_rate = double (item.second) / double (total_rtn_count);
      fout << item.first << " : " << item.second << ", " << total_rtn_count << ", " << call_rate << std::endl;
    }
  }

private:
  typedef OASIS::Pin::Buffer <Call_Rate> item_type;      // buffer type for a buffer of callback
  typedef std::list <item_type> list_type;               // list type of a list of buffers
  list_type rtn_buffer_list_;
};



/*******************************
 * Tool
 *******************************/

/**
 * Tool class for call rate.
 */
class callrate : public OASIS::Pin::Tool <callrate>
{
public:
  /**
   * Constructor.
   */
  callrate (void)
  {
    this->init_symbols ();
    this->enable_fini_callback ();
  }

  /**
   * Process after program execution.
   */
  void handle_fini (INT32 code)
  {
    // select between HASH and SORT for the implementation
    // sort: maybe slower for large program, but the result will be sorted
    // hash: maybe faster for large program, the result is not sorted
    enum choice_type {SORT, HASH};
    choice_type choice = SORT;

    // file output
    std::ofstream fout (outfile_.Value ().c_str ());
    fout.setf (ios::showbase);

    switch (choice)
    {
    case SORT:
      this->image_.output_to_file_by_sorting (fout);
      break;
    default:
      this->image_.output_to_file_by_hashmap (fout);
      break;
    }
  }

private:
  Image image_;                       // image level instrument
  static KNOB <string> outfile_;      // output file handler
};



KNOB <string> callrate::outfile_ (KNOB_MODE_WRITEONCE, "pintool", "o", "callrate.out", "specify output file name");



/*******************************
 * Tool declaration
 *******************************/

DECLARE_PINTOOL (callrate);