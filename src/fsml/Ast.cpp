#include "fsml/Ast.hpp"
namespace fsml
{

bool
operator==(const AstStep& lhs, const AstStep& rhs)
{
	return lhs.input == rhs.input && lhs.action == rhs.action && lhs.input == rhs.input;
}

bool
operator!=(const AstStep& lhs, const AstStep& rhs)
{
	return !operator==(lhs, rhs);
}


bool
operator==(const AstState& lhs, const AstState& rhs)
{
	return lhs.initial == rhs.initial && lhs.id == rhs.id && lhs.steps == rhs.steps;
}

bool
operator!=(const AstState& lhs, const AstState& rhs)
{
	return !operator==(lhs, rhs);
}


bool
operator==(const AstMachine& lhs, const AstMachine& rhs)
{
	return lhs.states == rhs.states;
}

bool
operator!=(const AstMachine& lhs, const AstMachine& rhs)
{
	return !operator==(lhs, rhs);
}

}
