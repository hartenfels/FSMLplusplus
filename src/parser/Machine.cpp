#include "parser/Machine.hpp"
#include <algorithm>
namespace fsml { namespace ast
{

const std::string
Machine::toString() const
{
	std::string r;
	std::for_each(states.begin(), states.end(),
			[&](const State& s){r += s.toString();});
	return r;
}

}}
