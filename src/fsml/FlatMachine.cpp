#include "FlatMachine.hpp"
#include "fsml/Parser.hpp"
namespace fsml
{

FlatMachine::FlatMachine(const AstMachine* const am)
{
    for (const AstState& state : am->states) {
        (state.initial.empty() ? states : initials).push_back(state.id);
		for (const AstStep& step : state.steps) {
			FlatStep fs{state.id, step.input, step.action,
					step.target.empty() ? state.id : step.target};
			steps.push_back(fs);
			// This will construct a new vector of FlatStep
			// if the source/target pair not yet in the map.
			stepMap[{fs.source, fs.target}].push_back(fs);
		}
	}
}

}
