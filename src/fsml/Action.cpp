#include "fsml/Action.hpp"
namespace fsml
{ using namespace std;

Action::Action(const string& i) : id{i} {}

const string&
Action::getId() const
{
	return id;
}

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
