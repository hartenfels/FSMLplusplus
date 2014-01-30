#ifndef FSML_STATE_HPP
#define FSML_STATE_HPP
#include "fsml/Step.hpp"
#include <string>
#include <unordered_map>
namespace fsml
{

/**Represents a Machine's state.*/
class State
{
public:
	/**Constructs a new State with the given id.
	@param id The State's name.*/
	State(const std::string& id, const bool& initial = false);
	virtual ~State() = default;

    /**Attemps to add the given transition to this State.
    @param input The input name.
    @param step The transition.
    @return false, if transition with the same input already exists, true otherwise.*/
	virtual bool addStep(const std::string& input, const Step& step);
    /**Attempts to execute the transition corresponding to the given input. If an action
    is triggered, the registered function will be called, if it exists.
    @param input The input name.
    @return The target State of the executed transition.
    @throws InvalidInputException if the input cannot be handled.*/
	virtual State* step(const std::string& input);
	/**@return If this State is an initial state.*/
	virtual const bool& isInitial() const;
	/**@return This State's name.*/
	virtual const std::string& getId() const;
	/**@return This State's transitions.*/
	virtual const std::unordered_map<std::string, Step>& getSteps() const;
protected:
	/// The State's initialness
	const bool initial;
    /// The State's id.
	const std::string id;
	/// The State's transitions.
	std::unordered_map<std::string, Step> steps;
};

}
#endif // FSML_STATE_HPP
