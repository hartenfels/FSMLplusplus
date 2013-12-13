#include "fsml/Step.hpp"
#include "fsml/Action.hpp"
#include "fsml/State.hpp"
namespace fsml
{

Step::Step(State* const t, Action* const a) :
	target(t), action(a) {}

State* const
Step::invoke()
{
	if (action)
		action->invoke();
	return target;
}

const State*
Step::getTarget() const
{
	return target;
}

}
