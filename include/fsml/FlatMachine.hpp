#ifndef FSML_FLATMACHINE_HPP
#define FSML_FLATMACHINE_HPP
#include "fsml/Ast.hpp"
#include "fsml/FlatStep.hpp"
#include <string>
#include <map>
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

	operator AstMachine() const;

    ///The non-inital states.
	std::vector<std::string> states;
	///The inital states.
	std::vector<std::string> initials;
	///The transitions.
	std::vector<FlatStep> steps;
	///Map from pair of states (source, target) to transitions.
	std::map<std::pair<std::string, std::string>, std::vector<std::string>> stepMap;
};

}
#endif // FSML_FLATMACHINE_HPP
