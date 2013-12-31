#ifndef FSML_PARSER_HPP
#define FSML_PARSER_HPP
#include "fsml/Exceptions.hpp"
#include "fsml/FlatMachine.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <string>
#include <vector>

namespace fsml
{

struct AstStep
{
	std::string input;
	std::string action;
	std::string target;
};

struct AstState
{
	std::string initial;
	std::string id;
	std::vector<AstStep> steps;
};

struct AstMachine
{
	std::vector<AstState> states;
};

}

BOOST_FUSION_ADAPT_STRUCT(fsml::AstState, (std::string, initial) (std::string, id)
		(std::vector<fsml::AstStep>, steps))

BOOST_FUSION_ADAPT_STRUCT(fsml::AstStep, (std::string, input)(std::string, action)
		(std::string, target))

namespace fsml
{

namespace qi = boost::spirit::qi;
namespace fsmlcs = boost::spirit::ascii;
template<typename Iterator>
struct FsmlGrammar :
	qi::grammar<Iterator, std::vector<AstState>(), fsmlcs::space_type>
{
	FsmlGrammar() :
		FsmlGrammar::base_type(fsm)
	{
		fsm        %= *state;
		state      %= initial >> "state" >> text >> '{' >> *transition >> '}';
		initial    %= -qi::lit("initial");
		transition %= text >> -('/' >> text) >> -("->" >> text) >> ';';
        text       %= qi::lexeme[+(fsmlcs::alpha)];
	}

	qi::rule<Iterator, std::vector<AstState>(), fsmlcs::space_type> fsm;
	qi::rule<Iterator, AstState(),              fsmlcs::space_type> state;
	qi::rule<Iterator, std::string(),           fsmlcs::space_type> initial;
    qi::rule<Iterator, AstStep(),               fsmlcs::space_type> transition;
    qi::rule<Iterator, std::string(),           fsmlcs::space_type> text;
};

template<typename Iterator>
FlatMachine parse(Iterator s, const Iterator& e, const std::string& f)
{
	AstMachine m;
	if (phrase_parse(s, e, FsmlGrammar<Iterator>(), fsmlcs::space, m.states) &&
			s == e) {
		return FlatMachine(&m);
	}
	throw ParserException(f);
}

}
#endif // FSML_PARSER_HPP
