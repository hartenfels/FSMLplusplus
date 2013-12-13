#ifndef FSML_STEP_HPP
#define FSML_STEP_HPP
namespace fsml
{
class Action;
class State;

class Step
{
public:
	Step(State* const target, Action* const action);
	virtual ~Step() = default;
	virtual State* const invoke();
	virtual const State* getTarget() const;
protected:
	State* const target;
	Action* const action;
};

}
#endif // FSML_STEP_HPP
