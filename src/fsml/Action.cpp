#include "fsml/Action.hpp"
namespace fsml
{

void
Action::registerFunction(const ActionFunction& f)
{
	func = f;
}

void
Action::invoke() const
{
	func();
}

}
