/**
 *
 * A pintool that calculates the call rate of each function in an executable
 *
 * File: callrate.cpp
 *
 */

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
#include <ctime>

/**
 * Process function calls and calculate call rate
 *
 */
class Call_Rate : public OASIS::Pin::Callback <Call_Rate (void)>
{
public:
  /**
   * Constructor.
   */
  Call_Rate (void)
    : rtn_name_ (""),
      rtn_count_ (0)
  {

  }

  /**
   * Call back procedure.
   *
   */
  void handle_analyze (void)
  {
    ++rtn_count_;
  }

  /**
   * Get the routine name.
   *
   * @return      returns the name of the routine
   */
  std::string rtn_name (void) const
  {
    return this->rtn_name_;
  }

  /**
   * Register the routine name.
   */
  void rtn_register (std::string rtn_name)
  {
    this->rtn_name_ = rtn_name;
  }

  /**
   * Get the routine count.
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


/**
 * Instrument at image level
 *
 */
class Image : public OASIS::Pin::Image_Instrument <Image>
{
public:
  /**
   * Instrument.
   */
  void handle_instrument (const OASIS::Pin::Image & img)
  {
    // first iteration
    // count total number of routines in the image
    UINT64 total_rtn_in_img = 0;
    for (OASIS::Pin::Section::iterator_type sec_iter = img.section_head (), sec_iter_end = sec_iter.make_end ();
         sec_iter != sec_iter_end;
         ++ sec_iter)
    {
      for (OASIS::Pin::Routine::iterator_type rtn_iter = sec_iter->routine_head (), rtn_iter_end = rtn_iter.make_end ();
           rtn_iter != rtn_iter_end;
           ++ rtn_iter)
      {
        ++total_rtn_in_img;
      }
    }
    
    // second iteration
    // pre-allocate one buffer for each image
    // the buffer size is equal to the number of routines in the image
    item_type item ((size_t) total_rtn_in_img);
    item_type::iterator callback = item.begin ();
    
    for (OASIS::Pin::Section::iterator_type sec_iter = img.section_head (), sec_iter_end = sec_iter.make_end ();
         sec_iter != sec_iter_end;
         ++ sec_iter)
    {
      for (OASIS::Pin::Routine::iterator_type rtn_iter = sec_iter->routine_head (), rtn_iter_end = rtn_iter.make_end ();
           rtn_iter != rtn_iter_end;
           ++ rtn_iter)
      {
        // automatically open and close the rtn for rtn_iter
        OASIS::Pin::Routine_Guard guard (*rtn_iter);
        callback->rtn_register (OASIS::Pin::Symbol::undecorate(rtn_iter->name(), UNDECORATION_NAME_ONLY));
        rtn_iter->insert_call (IPOINT_BEFORE, callback);
        ++callback;
      }
    }
    
    // the buffer list contains one buffer for each image
    this->img_rtn_buffer_.push_back (item);
  }

  /**
   * Calculate the total number of routine calls from all the images
   *
   * @return    total number of routine calls
   *
   */
  UINT64 total_count (void) const
  {
    list_type::const_iterator iter = this->img_rtn_buffer_.begin ();
    list_type::const_iterator iter_end = this->img_rtn_buffer_.end ();

    UINT64 total_rtn_count = 0;

    for (; iter != iter_end; ++ iter)
    {
      for (item_type::const_iterator item_iter = iter->begin (), item_iter_end = iter->end ();
           item_iter != item_iter_end;
           ++ item_iter)
      {
        total_rtn_count += item_iter->count ();
      }
    }

    return total_rtn_count;
  }

  /**
   * Generate an output of function call rate into a file.
   * The output format is: <routine name> : <callrate as double>.
   *
   * Each routine - count pair is pushed into a vector; the vector is sorted,
   * and the counts for the same routine are combined for output.
   *
   * @param[in]    output_file    the file pointer for output
   */
  void output_to_file_by_sorting (std::ofstream & fout)
  {
    UINT64 total_rtn_count = this->total_count();

    list_type::const_iterator iter = this->img_rtn_buffer_.begin ();
    list_type::const_iterator iter_end = this->img_rtn_buffer_.end ();

    // a vector of string - UINT64 pair
    typedef std::vector<std::pair<std::string, UINT64>> pair_vector;
    pair_vector pair_list;

    // iterate through the buffer and put the result into the vector
    for (; iter != iter_end; ++ iter)
    {
      for (item_type::const_iterator item_iter = iter->begin (), item_iter_end = iter->end ();
           item_iter != item_iter_end;
           ++ item_iter)
      {
        if (item_iter->count() > 0)
        {
          pair_list.push_back( std::pair<std::string, UINT64>( item_iter->rtn_name(), item_iter->count() ) );
        }
      }
    }
    
    // sort the vector so that same routine can be easily combined
    std::sort(pair_list.begin(), pair_list.end());
    size_t len = pair_list.size();

    // combine the count for the same routine and output the result to fout
    for (size_t i = 0; i < len; ++i)
    {
      std::string rtn_name = pair_list.at(i).first;
      UINT64 rtn_count = pair_list.at(i).second;
      while (i+1 < len && pair_list.at(i+1).first == rtn_name)
      {
        ++i;
        rtn_count += pair_list.at(i).second;
      }
      double call_rate = double(rtn_count) / double(total_rtn_count);
      fout << rtn_name << " : " << rtn_count << ", " << total_rtn_count << ", " << call_rate << std::endl;
    }
  }

  /**
   * Generate an output of function call rate into a file.
   * The output format is: <routine name> : <callrate as double>.
   *
   * Each routine - count is pushed into a hashmap. This hashmap is traversed for output.
   *
   * @param[in]    output_file    the file pointer for output
   */
  void output_to_file_by_hashmap (std::ofstream & fout)
  {
    UINT64 total_rtn_count = 0;

    list_type::const_iterator iter = this->img_rtn_buffer_.begin ();
    list_type::const_iterator iter_end = this->img_rtn_buffer_.end ();

    // a hashmap of string - UINT64
    stdext::hash_map<std::string, UINT64> map;

    std::string curr_name = "";
    UINT64 curr_count = 0;     

    // iterate through the buffer and put the result into the hashmap
    for (; iter != iter_end; ++ iter)
    {
      for (item_type::const_iterator item_iter = iter->begin (), item_iter_end = iter->end ();
           item_iter != item_iter_end;
           ++ item_iter)
      {
        curr_count = item_iter->count();
        if (curr_count > 0)
        {
          curr_name = item_iter->rtn_name();
          if ( map.count(curr_name) == 1 )
          {
            // routine already in the map, update the count
            stdext::hash_map<std::string, UINT64>::iterator it = map.find(curr_name);
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

    for (stdext::hash_map<std::string, UINT64>::iterator it = map.begin(); it != map.end(); ++it)
    {
      call_rate = double(it->second) / double(total_rtn_count);
      fout << it->first << " : " << it->second << ", " << total_rtn_count << ", " << call_rate << std::endl;
    }
  }

private:
  typedef OASIS::Pin::Buffer <Call_Rate> item_type;
  typedef std::list <item_type> list_type;
  list_type img_rtn_buffer_;
};


/**
 * Tool for call rate
 *
 */
class callrate : public OASIS::Pin::Tool <callrate>
{
public:
  /**
   * Constructor.
   */
  callrate (void)
  {
    this->init_symbols();
    this->enable_fini_callback();
  }
    
  /**
   * Process after program execution.
   */
  void handle_fini (INT32 code)
  {
    std::string choice = "sort";

    // file output
    std::ofstream fout (outfile_.Value ().c_str ());
    fout.setf (ios::showbase);
    
    // std::clock_t start = std::clock();

    if (choice == "sort")
    {
      this->image_.output_to_file_by_sorting (fout);
    }
    else if (choice == "hash")
    {
      this->image_.output_to_file_by_hashmap (fout);
    }

    // std::clock_t end = std::clock();
    // std::cout << "Time used by " << choice << ": "
    //           << 1000.0 * (end - start) / CLOCKS_PER_SEC << " ms." << std::endl;
  }

private:
  Image image_;                       // image level instrument
  static KNOB <string> outfile_;      // output file handler
};

KNOB <string> callrate::outfile_ (KNOB_MODE_WRITEONCE, "pintool", "o", "callrate.out", "specify output file name");

/**************************
 * Tool registration
 **************************/
DECLARE_PINTOOL (callrate);
