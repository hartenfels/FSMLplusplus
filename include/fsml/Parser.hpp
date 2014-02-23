#ifndef FSML_PARSER_HPP
#define FSML_PARSER_HPP
#include "fsml/Ast.hpp"
#include "fsml/Exceptions.hpp"
#include "fsml/FlatMachine.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <string>
#include <vector>
/**@file Contains the parser and all related structures.
Since all functions require templates, the entire implementation resides in this header
file. There is no separat implementation file.*/

/**Adapt state and step structs for use with Boost.Spirit.Qi.*/
BOOST_FUSION_ADAPT_STRUCT(fsml::AstState, (std::string, initial) (std::string, id)
		(std::vector<fsml::AstStep>, steps))
BOOST_FUSION_ADAPT_STRUCT(fsml::AstStep, (std::string, input)(std::string, action)
		(std::string, target))

namespace fsml
{ namespace qi = boost::spirit::qi; namespace fsmlcs = boost::spirit::ascii;

/**Definition of fsml grammar in Boost.Spirit.Qi.
@tparam Iterator The random access iterator to use.*/
template<typename Iterator>
struct FsmlGrammar : qi::grammar<Iterator, std::vector<AstState>(), fsmlcs::space_type>
{
    /**Constructs a Boost.Spirit.Qi grammar as given for parsing fsml.*/
	FsmlGrammar() :
		FsmlGrammar::base_type(fsm)
	{
		fsm        %= *state;
		state      %= initial >> "state" >> text >> '{' >> *transition >> '}';
		initial    %= -qi::lit("initial");
		transition %= text >> -('/' >> text) >> -("->" >> text) >> ';';
        text       %= qi::lexeme[fsmlcs::alpha >> +(fsmlcs::alnum)];
	}

    ///Qi rule for fsm : {state}*, returns vector of AstState.
	qi::rule<Iterator, std::vector<AstState>(), fsmlcs::space_type> fsm;
    ///Qi rule for state : initial 'state' text '{' {transition}* '}', returns AstState.
	qi::rule<Iterator, AstState(),              fsmlcs::space_type> state;
	///Qi rule for initial : {'initial'}?, returns "initial" or empty string.
	qi::rule<Iterator, std::string(),           fsmlcs::space_type> initial;
	///Qi rule for transition : text {'/' text}? {'->' text}? ';', returns AstStep.
    qi::rule<Iterator, AstStep(),               fsmlcs::space_type> transition;
    ///Qi rule for text : [a-zA-Z]+, returns parsed string.
    qi::rule<Iterator, std::string(),           fsmlcs::space_type> text;
};

/**Parses fsml code from the given iterators and flattens the resulting abstract syntax
tree.
@tparam Iterator The random access iterator to use.
@param s Iterator to beginning of code.
@param e Iterator to end of code.
@param f File name for error message.
@return A FlatMachine representing the flattened abstract syntax tree.
@throws ParserException if the given code is not well formed.*/
template<typename Iterator>
FlatMachine parse(Iterator s, const Iterator& e, const std::string& f = std::string{})
{
	AstMachine m;
	if (phrase_parse(s, e, FsmlGrammar<Iterator>(), fsmlcs::space, m.states) &&
			s == e) {
		return FlatMachine(m);
	}
	throw ParserException(f);
}

}
#endif // FSML_PARSER_HPP
