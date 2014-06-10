#include "ExPAD_Config.h"
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include "boost/spirit/include/phoenix_fusion.hpp"
#include "boost/spirit/include/phoenix_bind.hpp"
#include "boost/config/warning_disable.hpp"
#include "boost/spirit/include/qi.hpp"
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/qi_char_class.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
#include "boost/spirit/include/phoenix_container.hpp"
#include <fstream>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename IteratorT>
struct ExPAD_Config_Parser_Grammar :
    public qi::grammar <IteratorT,
                        void (ExPAD_Config *),
                        ascii::space_type>
{
  ExPAD_Config_Parser_Grammar (void) :
    ExPAD_Config_Parser_Grammar::base_type (this->config_)
  {
    namespace qi = boost::spirit::qi;
    namespace phoenix = boost::phoenix;
    namespace ascii = boost::spirit::ascii;

    this->ident_ %= qi::lexeme[+(qi::alpha | qi::alnum | ascii::char_ ('_') | 
                    ascii::char_ ('.') | ascii::char_ (':') | ascii::char_ ('?') |
                    ascii::char_ ('@') | ascii::char_ ('-'))];

    this->include_dlls_ = ascii::string ("Include_Shared_Libraries") >> 
                          ascii::char_('=') >> 
                          *(this->ident_[qi::_a = qi::_1] >> 
                          ascii::char_(",")[phoenix::bind (&ExPAD_Config::insert_to_dll_includes, qi::_r1, qi::_a)]) >> 
                          this->ident_[qi::_b = qi::_1] >>
                          ascii::char_(";")[phoenix::bind (&ExPAD_Config::insert_to_dll_includes, qi::_r1, qi::_b)];

   this->include_function_entry_ = ascii::string ("[Shared_Library_Name") >>
                                    ascii::char_ ('=') >> 
                                    this->ident_[qi::_a = qi::_1] >>
                                    ascii::char_(";") >> 
                                    ascii::string ("Function_Starting_With") >> 
                                    ascii::char_('=') >>
                                    *(this->ident_[qi::_b = qi::_1] >> 
                                    ascii::char_(",")[phoenix::bind (&ExPAD_Config::insert_to_function_includes, qi::_r1, qi::_a, qi::_b)]) >> 
                                    this->ident_[qi::_c = qi::_1] >>
                                    ascii::char_(";")[phoenix::bind (&ExPAD_Config::insert_to_function_includes, qi::_r1, qi::_a, qi::_c)] >>
                                    ascii::char_ ("]");

    this->include_functions_ = ascii::string ("Include_Functions_IN") >>
                               ascii::char_ ("{") >>
                               *(this->include_function_entry_ (qi::_r1)) >>
                               ascii::char_ ("}");
    
    this->config_ = (this->include_dlls_ (qi::_r1) >> this->include_functions_ (qi::_r1)) | 
                    this->include_dlls_ (qi::_r1) | this->include_functions_ (qi::_r1);
    
 }

private:

  qi::rule <IteratorT,
            void (ExPAD_Config *),
            ascii::space_type> config_;
  
  qi::rule <IteratorT,
            void (ExPAD_Config *),
            qi::locals <std::string, std::string>,
            ascii::space_type> include_dlls_;
  
  qi::rule <IteratorT,
            void (ExPAD_Config *),
            ascii::space_type> include_functions_;
  
  qi::rule <IteratorT,
            void (ExPAD_Config *),
            qi::locals <std::string, std::string, std::string>,
            ascii::space_type> include_function_entry_;
  
  qi::rule <IteratorT,
            std::string (),
            ascii::space_type> ident_;

};


ExPAD_Config::ExPAD_Config (void)
{

}

ExPAD_Config::~ExPAD_Config (void)
{

}

bool ExPAD_Config::read_config (void)
{
  // parse the config file and populate the 
  // data structures

  namespace spirit = boost::spirit;
  namespace qi = boost::spirit::qi;
  namespace ascii = boost::spirit::ascii;

  std::ifstream input ("ExPAD.config");

  // Adapt the iterator to support Boost backtracking.
  long flags = input.flags ();

  if ((flags & std::ios::skipws) != 0)
    input.unsetf (std::ios::skipws);

  spirit::istream_iterator begin (input);
  spirit::istream_iterator end;

  ExPAD_Config_Parser_Grammar <spirit::istream_iterator> grammar;

  bool ret_val =  qi::phrase_parse (begin,
                                    end,
                                    grammar (this),
                                    ascii::space);

  if ((flags & std::ios::skipws) != 0)
    input.setf (std::ios::skipws);

  if (!ret_val)
    std::cerr << "Parsing failed" << std::endl;
  else
    std::cerr << "Parsing succeed" << std::endl;

  return ret_val;
}

bool ExPAD_Config::ignore_routine (std::string & image_name, 
                                   std::string & func_name)
{
  STRING_SET::iterator it = this->dll_includes_.find (image_name);

  if (it == this->dll_includes_.end ())
  {
    FUNCTIONS::iterator it1 = this->function_includes_.find (image_name);
    
    if (it1 == this->function_includes_.end ())
      return true;
    else
    {
      STRING_SET::iterator iter = it1->second.begin (), 
        iter_end = it1->second.end ();

      for (; iter != iter_end; iter++)
      {
        if (func_name.find (*iter) == 0)
          return false;
      }

      return true;
    }
  }
  else
    return false;
}

void ExPAD_Config::insert_to_dll_includes (std::string & dll_name)
{
  this->dll_includes_.insert (dll_name);
}

void ExPAD_Config::insert_to_function_includes (std::string & dll_name, 
                                               std::string & func_name)
{
  FUNCTIONS::iterator it = this->function_includes_.find (dll_name);

  if (it == this->function_includes_.end ())
  {
    STRING_SET temp;
    temp.insert (func_name);
    this->function_includes_.insert (std::pair <std::string, STRING_SET> (dll_name, temp));
  }
  else
  {
    it->second.insert (func_name);
  }
}