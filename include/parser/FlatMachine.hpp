#ifndef FSML_FLATMACHINE_HPP
#define FSML_FLATMACHINE_HPP
#include "parser/Machine.hpp"
namespace fsml
{

struct FlatStep {
	FlatStep(const std::string& source, const std::string& input,
			const std::string& action, const std::string& target);
	~FlatStep() = default;

	operator std::string() const;

    std::string source;
    std::string input;
    std::string action;
    std::string target;
};

struct FlatMachine {
	FlatMachine(const ast::Machine& am);
	~FlatMachine() = default;

	std::vector<std::string> states;
	std::vector<std::string> initials;
	std::vector<FlatStep> steps;
};

}
#endif // FSML_FLATMACHINE_HPP
