#ifndef FSML_PARSER_MACHINE_HPP
#define FSML_PARSER_MACHINE_HPP
#include "parser/State.hpp"
#include <string>
#include <vector>
namespace fsml { namespace ast
{

struct Machine {
	const std::string toString() const;

	std::vector<State> states;
};

}}

#endif // FSML_PARSER_MACHINE_HPP
