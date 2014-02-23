#ifndef FSML_MACHINE_HPP
#define FSML_MACHINE_HPP
#include "fsml/Action.hpp"
#include "fsml/FlatMachine.hpp"
#include "fsml/State.hpp"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
namespace fsml
{

/**Represents a simulatable final state machine.*/
class Machine
{
public:
    /**Constructs and validates a Machine from the given FlatMachine.
    @param fm The FlatMachine.
    @return A Machine corresponding to the given FlatMachine, if it is valid.
    @throw InitialStateException if no or more then one inital state is given.
    @throw UniqueException if a state is defined more than once.
    @throw ReachableException if a state is not reachable from intial state.
    @throw ResolvableException if target state in a transition does not exist.
    @throw DeterministicException if an input in a state is not distinct.*/
	Machine(const FlatMachine& fm);
	/**Constructs and validates a Machine from the given parameters.
    @param initials The initial states.
    @param states The non-inital states.
    @param steps The transitions.
    @return A Machine corresponding to the given parameters, if they are valid.
    @throw InitialStateException if no or more then one inital state is given.
    @throw UniqueException if a state is defined more than once.
    @throw ReachableException if a state is not reachable from intial state.
    @throw ResolvableException if target state in a transition does not exist.
    @throw DeterministicException if an input in a state is not distinct.*/
	Machine(const std::vector<std::string>& initials,
		const std::vector<std::string>& states,
		const std::vector<FlatStep>& steps);
	virtual ~Machine() = default;

    /**Feeds the given input into the Machine. The current State will attempt to execute
    the corresponding transition and change the current State.
    If an action is triggered, the registered function will be called, if it exists.
    @param input The input name.
    @return The Machine itself so that input can be chained.
    @throw InvalidInputException if the current State cannot handle the input. The
    current State will not be changed.*/
	virtual Machine& operator<<(const std::string& input);

	virtual operator FlatMachine() const;

    /**Gathers the States reachable from the given State.
    @param start The State from which to start from.
    @return An unordered set of states reachable from start.*/
	virtual const std::unordered_set<const State*>
		reachableFrom(const State* const start) const;

    /**Registers the given function with the given action.
    @param action The action name.
    @param func The function to register.
    @throw out_of_range if the action does not exist.*/
	virtual void registerAt(const std::string& action,
		const ActionFunction& func);

    /**@return The current State.*/
	virtual const State& getCurrentState() const;

protected:
    /**Constructs a step from the given parameters and adds it to the source state.
    @param sourcId The source state's name.
    @param input The input name.
    @param actionId The action name.
    @param targetId The target state's name.
    @throw ResolvableException if target does not exist.
    @throw DeterministicException if there is more than one possible transition for the
    given input.*/
	void addStep(const std::string& sourceId, const std::string& input,
		const std::string& actionId, const std::string& targetId);

    ///Maps actions to their respective name.
	std::unordered_map<std::string, Action> actionMap;
    ///Maps states to their respective name.
	std::unordered_map<std::string, State> stateMap;
	///The current State
	State* current;
};

}
#endif // FSML_MACHINE_HPP
