#ifndef FSML_MACHINE_HPP
#define FSML_MACHINE_HPP
#include "fsml/Action.hpp"
#include "fsml/State.hpp"
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
namespace fsml
{

typedef std::tuple<std::string, std::string, std::string, std::string> StepTup;

class Machine
{
public:
	Machine(const std::vector<std::string>& states, const std::string& initial,
		const std::vector<StepTup>& steps);
	virtual ~Machine() = default;
	virtual Machine& operator<<(const std::string& input);
	virtual const size_t reachableFrom(const State* const start) const;
	virtual void registerAt(const std::string& action,
		const ActionFunction& func);
protected:
	void addStep(const std::string& sourceId, const std::string& input,
		const std::string& actionId, const std::string& targetId);

	std::unordered_map<std::string, Action> actionMap;
	std::unordered_map<std::string, State> stateMap;
	State* current;
};

}
#endif // FSML_MACHINE_HPP
