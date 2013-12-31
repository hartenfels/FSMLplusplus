#ifndef FSML_FLATMACHINE_HPP
#define FSML_FLATMACHINE_HPP
#include "fsml/FlatStep.hpp"
#include <string>
#include <vector>
namespace fsml
{
struct AstMachine;

struct FlatMachine {
	FlatMachine(const AstMachine* const am);
	~FlatMachine() = default;

	std::vector<std::string> states;
	std::vector<std::string> initials;
	std::vector<FlatStep> steps;
};

}
#endif // FSML_FLATMACHINE_HPP
