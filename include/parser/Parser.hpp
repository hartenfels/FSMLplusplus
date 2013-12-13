#ifndef FSML_PARSER_PARSER_HPP
#define FSML_PARSER_PARSER_HPP
#include "parser/Machine.hpp"
#include "parser/State.hpp"
#include "parser/Step.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <string>
#include <vector>

BOOST_FUSION_ADAPT_STRUCT(
	fsml::ast::State,
	(std::string, initial)
	(std::string, id)
	(std::vector<fsml::ast::Step>, steps)
)

BOOST_FUSION_ADAPT_STRUCT(
	fsml::ast::Step,
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
struct FsmlGrammar :
	qi::grammar<Iterator, std::vector<ast::State>(), fsmlcs::space_type>
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

	qi::rule<Iterator, std::vector<ast::State>(), fsmlcs::space_type> fsm;
	qi::rule<Iterator, ast::State(),              fsmlcs::space_type> state;
	qi::rule<Iterator, std::string(),             fsmlcs::space_type> initial;
    qi::rule<Iterator, ast::Step(),               fsmlcs::space_type> transition;
    qi::rule<Iterator, std::string(),             fsmlcs::space_type> text;
};

template<typename Iterator>
ast::Machine parse(Iterator s, const Iterator& e)
{
	ast::Machine m;
	if (phrase_parse(s, e, FsmlGrammar<Iterator>(), fsmlcs::space, m.states) &&
			s == e) {
		return m;
	}
	throw 0;
}

}}
#endif // FSML_PARSER_PARSER_HPP
