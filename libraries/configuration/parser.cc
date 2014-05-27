/*
 * debug.cc
 *
 *  Created on: 8 mars 2013
 *      Author: hadrien
 */

#include "parser.hh"
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

namespace qi = boost::spirit::qi;
//namespace ascii = boost::spirit::ascii;
namespace standard = boost::spirit::standard;
 
// We need to tell fusion about our struct
// to make it a first-class fusion citizen. This has to
// be in global scope according to official Boost Spirit tutorial.

BOOST_FUSION_ADAPT_STRUCT(
			  configuration::ShapeListener,
			  (int, key)
			  (float, coef)
			  (std::string, gain)
			  )

BOOST_FUSION_ADAPT_STRUCT(
			  configuration::ShapeInfo,
			  (std::string, name)
			  (std::vector<std::string>, attributes)
			  (std::vector<configuration::ShapeListener>, listeners)
			  )

BOOST_FUSION_ADAPT_STRUCT(
			  configuration::TrialInfo,
			  (std::string, name)
			  (std::vector<std::string>, attributes)
			  (std::vector<configuration::ShapeInfo>, shapes)
			  )

BOOST_FUSION_ADAPT_STRUCT(
			  configuration::SessionInfo,
			  (std::string, name)
                          (std::string, x_channel)
                          (std::string, y_channel)
			  (std::string, save)
                          (int, traceLevel)
                          (int, frequency)
			  (int, width)
			  (int, height)
			  (int, nb_screens)
			  (int, nb_trials)
			  (int, shuffle)
			  (std::vector<configuration::TrialInfo>, trials)
			  )


namespace configuration
{
  ///////////////////////////////////////////////////////////////////////////////
  //  Our moses parser
  ///////////////////////////////////////////////////////////////////////////////
  template <typename Iterator>
  struct moses_parser : qi::grammar<Iterator, SessionInfo(), standard::space_type>
  {
    moses_parser() : moses_parser::base_type(session)
    {
      using qi::int_;
      using qi::lit;
      using qi::double_;
      using qi::float_;
      using qi::lexeme;
      using standard::char_;
      using boost::fusion::vector;
      using qi::eol;

      word %= lexeme[ +(char_ - ' ' - "|" - "+" - ">" -  ";" - "\n")];
      
      listener %= "+" 
        >> int_
	>> float_
	>> word
	;

      shape %= ">"
	>> word // Shape name
	>> +word // Shape attributes
       	>> *listener
	;

      trial %= "|"

	>> word
	>> +word
	>> +shape
	>> ";"
	;

      session %=
	-("name=">> word)
        >> -("x_channel=" >> word)
        >> -("y_channel=" >> word)
	>> -("save=" >> word) 
        >> -("logLevel=" >> int_)
        >> ("frequency=" >> int_)
        >> ("width=" >> int_)
	>> ("height=" >> int_)
	>> ("nb_screens=" >> int_)
	>> ("nb_trials=" >> int_)
	>> ("shuffle=" >> int_)
	>> +trial
	;

    }

    qi::rule<Iterator, std::string(), standard::space_type> word;

    qi::rule<Iterator, configuration::ShapeListener(), standard::space_type> listener;
    qi::rule<Iterator, configuration::ShapeInfo(), standard::space_type> shape;
    qi::rule<Iterator, configuration::TrialInfo(), standard::space_type> trial;
    qi::rule<Iterator, configuration::SessionInfo(), standard::space_type> session;
  };

  ////////////////////////////////////////////////////////////////////////////
  //  Main program
  ////////////////////////////////////////////////////////////////////////////
  bool	CreateConfiguration(char const* filename,
			    SessionInfo &res)
  {
    std::ifstream in(filename, std::ios_base::in);
    if (!in)
      {
	std::cerr << "Error: Could not open input file: "
		  << filename << std::endl;
	return false;
      }
    in.unsetf(std::ios::skipws); // No white space skipping!
    std::string storage; // We will read the contents here.
    std::copy(
	      std::istream_iterator<char>(in),
	      std::istream_iterator<char>(),
	      std::back_inserter(storage));

    using boost::spirit::standard::space;

    typedef std::string::const_iterator iterator_type;
    typedef configuration::moses_parser<iterator_type> moses_parser;

    moses_parser g; // Our grammar

    std::string::const_iterator iter = storage.begin();
    std::string::const_iterator end = storage.end();

    bool r = boost::spirit::qi::phrase_parse(iter, end, g, space, res);

    if (!r)
    {
      std::cout << "parsing failed, your definition file is not valid" << std::endl;
      throw;
    }

    return (r);
  }

}

