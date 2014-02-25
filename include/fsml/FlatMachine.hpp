#ifndef FSML_FLATMACHINE_HPP
#define FSML_FLATMACHINE_HPP
#include "fsml/Ast.hpp"
#include "fsml/FlatStep.hpp"
#include <string>
#include <unordered_map>
#include <vector>
namespace fsml
{

/**Flat representation of the abstract syntax tree.*/
struct FlatMachine
{
    FlatMachine() = default;
	/**Constructs a flattened representation of the given abstract syntax tree machine.
    @param am Abstract syntax tree to generate from.*/
	FlatMachine(const AstMachine& am);
	~FlatMachine() = default;

	/**Converts this FlatMachine into an equivalent, minimal abstract syntax tree.*/
	operator AstMachine() const;
	/**Converts this FlatMachine into a string.*/
	operator std::string() const;

    /// The non-inital states.
	std::vector<std::string> states;
	/// The inital states.
	std::vector<std::string> initials;
	/// The transitions.
	std::vector<FlatStep> steps;
};

/**Checks if two FlatMachines are equal based on their states, initials and steps. Their
order is significant. The stepMap is diregarded.*/
bool operator==(const FlatMachine& lhs, const FlatMachine& rhs);
bool operator!=(const FlatMachine& lhs, const FlatMachine& rhs);

}
#endif // FSML_FLATMACHINE_HPP
