#ifndef FSML_FLATMACHINE_HPP
#define FSML_FLATMACHINE_HPP
#include "fsml/Ast.hpp"
#include "fsml/FlatStep.hpp"
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
namespace fsml
{

/**Flat representation of the abstract syntax tree.*/
struct FlatMachine
{
    /**Constructs a flattened representation of the given abstract syntax tree machine.
    @param am Abstract syntax tree to generate from.*/
    FlatMachine() = default;
	FlatMachine(const AstMachine& am);
	~FlatMachine() = default;

	void addStep(FlatStep fs);
	operator AstMachine() const;
	operator std::string() const;

    ///The non-inital states.
	std::vector<std::string> states;
	///The inital states.
	std::vector<std::string> initials;
	///The transitions.
	std::vector<FlatStep> steps;
	///Map from pair of states (source, target) to transitions.
	std::map<std::pair<std::string, std::string>, std::vector<std::string>> stepMap;
};

bool operator==(const FlatMachine& lhs, const FlatMachine& rhs);
bool operator!=(const FlatMachine& lhs, const FlatMachine& rhs);

}
#endif // FSML_FLATMACHINE_HPP
