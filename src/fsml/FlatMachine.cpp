#include "FlatMachine.hpp"
#include <algorithm>
namespace fsml
{ using namespace std;

FlatMachine::FlatMachine(const AstMachine& am)
{
    for (const AstState& state : am.states) {
        (state.initial.empty() ? states : initials).insert(state.id);
		for (const AstStep& step : state.steps) {
			FlatStep fs{state.id, step.input, step.action,
					step.target.empty() ? state.id : step.target};
			steps.insert(fs);
			// This will construct a new vector of FlatStep
			// if the source/target pair not yet in the map.
			stepMap[{fs.source, fs.target}].push_back(fs.getStepText());
		}
	}
}

FlatMachine::operator AstMachine() const
{
	AstMachine am;
	for (const string& i : initials)
		am.states.push_back({"initial", i, {}});
	for (const string& s : states)
		am.states.push_back({"", s, {}});
	for (const FlatStep& step : steps)
        find_if(am.states.begin(), am.states.end(), [&](const AstState& state){
					return state.id == step.source;
				})->steps.push_back(
				{step.input, step.action, step.target == step.source ? "" : step.target});
	return am;
}

}
