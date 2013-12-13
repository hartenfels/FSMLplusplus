#ifndef FSML_PARSER_STEP_H
#define FSML_PARSER_STEP_H
#include <string>
namespace fsml { namespace ast
{

struct Step {
	const std::string toString() const;

	std::string input;
	std::string action;
	std::string target;
};

}}

#endif // FSML_PARSER_STEP_H
