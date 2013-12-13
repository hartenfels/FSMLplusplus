#include "parser/State.hpp"
#include <algorithm>
namespace fsml { namespace ast
{

const std::string
State::toString() const
{
	std::string r((initial.empty() ? id : initial + ' ' + id) + " {\n");
	std::for_each(steps.begin(), steps.end(),
			[&](const Step& s){r += '\t' + s.toString();});
	return r + "}\n";
}

}}
