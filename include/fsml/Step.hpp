#ifndef FSML_STEP_HPP
#define FSML_STEP_HPP
namespace fsml
{
class Action;
class State;

/**Represents a State's transition.*/
class Step
{
public:
    /**Constructs a new Step with the given action and target.
    @param target The target State.
    @param action The Action for this Step, or nullptr if there is none.*/
	Step(State* const target, Action* const action);
	virtual ~Step() = default;

    /**Invokes the this Step's Action, if it exists.
    @return The target of the action.*/
	virtual State* invoke();
	/**@return The target State.*/
	virtual const State* getTarget() const;
	/**@return The Action, or nullptr if there is none.*/
	virtual const Action* getAction() const;
protected:
    ///The target State.
	State* const target;
	///The Action, if it exists, otherwise nullptr.
	Action* const action;
};

}
#endif // FSML_STEP_HPP
