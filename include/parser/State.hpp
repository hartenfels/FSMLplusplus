#ifndef FSML_PARSER_STATE_HPP
#define FSML_PARSER_STATE_HPP
#include "parser/Step.hpp"
#include <string>
#include <vector>
namespace fsml { namespace ast
{

struct State {
	const std::string toString() const;

	std::string initial;
	std::string id;
	std::vector<Step> steps;
};

}}
#endif // FSML_PARSER_STATE_HPP
