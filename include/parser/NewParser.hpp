#ifndef FSML_NEW_PARSER_HPP
#define FSML_NEW_PARSER_HPP
#include <iostream>
#include <string>
#include <vector>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
namespace fsml { namespace parser
{
struct Transition {
	std::string input;
	std::string action;
	std::string target;
};
}}
BOOST_FUSION_ADAPT_STRUCT(
	fsml::parser::Transition,
	(std::string, input)
	(std::string, action)
	(std::string, target)
)
namespace fsml { namespace parser
{

namespace qi = boost::spirit::qi;
namespace fsmlcs = boost::spirit::ascii;
namespace ast = fsml::ast;
template<typename Iterator>
struct NewFsmlGrammar : qi::grammar<Iterator, fsmlcs::space_type>
{
	NewFsmlGrammar() :
		NewFsmlGrammar::base_type{fsm}
	{
		fsm        = *state[[](){std::cout << "state done\n";}];
		state      = initial >> "state" >> text[[](){std::cout << "name\n";}] >>
		             '{' >> *transition[[](){std::cout << "transition\n";}] >> '}';
		initial    = -qi::lit("initial")[[](){std::cout << "initial\n";}];
		transition %= text >> -('/' >> text) >> -("->" >> text) >> ';';
        text       = qi::lexeme[+(fsmlcs::alpha)];
	}
	qi::rule<Iterator, fsmlcs::space_type> fsm;
	qi::rule<Iterator, fsmlcs::space_type> state;
	qi::rule<Iterator, fsmlcs::space_type> initial;
    qi::rule<Iterator, Transition, fsmlcs::space_type> transition;
    qi::rule<Iterator, fsmlcs::space_type> text;
};

template<typename Iterator>
void newParse(Iterator s, const Iterator& e)
{
	if (phrase_parse(s, e, NewFsmlGrammar<Iterator>(), fsmlcs::space) && s == e) {
		return;
	}
	throw 0;
}

}}
#endif // FSML_NEW_PARSER_HPP
