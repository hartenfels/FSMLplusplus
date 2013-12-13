#include "parser/Step.hpp"
namespace fsml { namespace ast
{

const std::string
Step::toString() const
{
	return input + (action.empty() ? "" : '/' + action) +
			(target.empty() ? "" : " -> " + target) + ";\n";
}

}}
