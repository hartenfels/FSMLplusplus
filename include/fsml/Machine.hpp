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

class Machine
{
public:
	Machine(const FlatMachine& fm);
	Machine(const std::vector<std::string>& initials,
		const std::vector<std::string>& states,
		const std::vector<FlatStep>& steps);

	virtual ~Machine() = default;

	virtual Machine& operator<<(const std::string& input);

	virtual const std::unordered_set<const State*>
		reachableFrom(const State* const start) const;

	virtual void registerAt(const std::string& action,
		const ActionFunction& func);

	virtual const State& getCurrentState() const;

protected:
	void addStep(const std::string& sourceId, const std::string& input,
		const std::string& actionId, const std::string& targetId);

	std::unordered_map<std::string, Action> actionMap;
	std::unordered_map<std::string, State> stateMap;
	State* current;
};

}
#endif // FSML_MACHINE_HPP
