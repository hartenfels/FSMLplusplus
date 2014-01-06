#ifndef FSML_FLATSTEP_HPP
#define FSML_FLATSTEP_HPP
#include <string>
namespace fsml
{

/**Flat representation of a transition.*/
struct FlatStep
{
    /**Constructs the flattened transition.
    @param source Source state.
    @param input Input name.
    @param action Action name or empty string for no action.
    @param target Target state or empty string for source being target.*/
	FlatStep(const std::string& source, const std::string& input,
			const std::string& action, const std::string& target);
	~FlatStep() = default;

    /**Converts this FlatStep to a string.*/
	operator std::string() const;
	/**@return The text for the transition (input or input/action).*/
	const std::string getStepText() const;

    ///The source state.
    std::string source;
    ///The input name.
    std::string input;
    ///The action name or empty string for no action.
    std::string action;
    ///The target state.
    std::string target;
};

}
#endif // FSML_FLATSTEP_HPP
