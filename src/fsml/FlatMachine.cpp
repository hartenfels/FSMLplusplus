#include "FlatMachine.hpp"
#include "fsml/Parser.hpp"
namespace fsml
{

FlatMachine::FlatMachine(const AstMachine* const am)
{
    for (const AstState& state : am->states) {
        (state.initial.empty() ? states : initials).push_back(state.id);
		for (const AstStep& step : state.steps)
			steps.push_back(FlatStep{state.id, step.input, step.action,
					step.target.empty() ? state.id : step.target});
	}
}

}
