#include "FlatMachine.hpp"
#include <algorithm>
#include <sstream>
namespace fsml
{ using namespace std;

FlatMachine::FlatMachine(const AstMachine& am)
{
    for (const AstState& state : am.states) {
        (state.initial.empty() ? states : initials).push_back(state.id);
		for (const AstStep& step : state.steps)
			addStep({state.id, step.input, step.action,
					step.target.empty() ? state.id : step.target});
	}
}

void
FlatMachine::addStep(FlatStep fs)
{
	steps.push_back(fs);
	// This will construct a new vector of FlatStep
	// if the source/target pair not yet in the map.
	stepMap[{fs.source, fs.target}].push_back(fs.getStepText());
}

FlatMachine::operator AstMachine() const
{
	AstMachine am;
	for (const string& i : initials)
		am.states.push_back({"initial", i, {}});
	for (const string& s : states)
		am.states.push_back({string{}, s, {}});
	for (const FlatStep& step : steps)
        find_if(am.states.begin(), am.states.end(), [&](const AstState& state){
					return state.id == step.source;
				})->steps.push_back(
				{step.input, step.action, step.target == step.source ? "" : step.target});
	return am;
}

FlatMachine::operator string() const
{
	stringstream ss;
	ss << "states:";
	for (const string& s : states)
		ss << ' ' << s;
	ss << "\ninitials:";
	for (const string& s : initials)
		ss << ' ' << s;
	ss << "\nsteps:";
	for (const string& s : steps)
		ss << ' ' << s;
	return ss.str();
}

bool
operator==(const FlatMachine& lhs, const FlatMachine& rhs)
{
	return lhs.states == rhs.states && lhs.initials == rhs.initials &&
			lhs.steps == rhs.steps;
}

bool
operator!=(const FlatMachine& lhs, const FlatMachine& rhs)
{
	return !operator==(lhs, rhs);
}

}
