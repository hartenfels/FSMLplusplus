#include "FlatMachine.hpp"
#include <boost/format.hpp>
namespace fsml
{ using boost::format;

FlatStep::FlatStep(const std::string& s, const std::string& i,
		const std::string& a, const std::string& t) :
	source{s}, input{i}, action{a}, target{t} {}

FlatStep::operator std::string() const
{
	return (format("FlatStep(\"%1%\", \"%2%\", \"%3%\", \"%4%\")") % source %
			input % action % target).str();
}


FlatMachine::FlatMachine(const ast::Machine& am)
{
    for (const ast::State& state : am.states) {
        (state.initial.empty() ? states : initials).push_back(state.id);
		for (const ast::Step& step : state.steps)
			steps.push_back(FlatStep{state.id, step.input, step.action,
					step.target.empty() ? state.id : step.target});
	}
}

}
