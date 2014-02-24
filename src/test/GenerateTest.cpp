#include "GenerateTest.hpp"
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/visitors.hpp>
namespace fsml
{ using namespace std; using namespace boost; using namespace boost::multiprecision;

static FlatStep
genStep(const cpp_int& pos, const cpp_int& num,
		const cpp_int& states)
{
	const cpp_int source = (pos / num) % states;
	const cpp_int target = (pos / (num * states)) % states;
	return {"s" + source.str(), "input" + pos.str(), "", "s" + target.str()};
}

FlatMachine
generateFlatMachine(const size_t& ni, const size_t& ns, const cpp_int& t)
{
    FlatMachine fm;
    size_t stateCount = 0;
	fm.initials.reserve(ni);
    for (stateCount = 0; stateCount < ni; ++stateCount)
		fm.initials.push_back("s" + to_string(stateCount));
	fm.states.reserve(ns);
	for (size_t i = 0; i < ns; ++i, ++stateCount)
		fm.states.push_back("s" + to_string(stateCount));

	const cpp_int states = stateCount;
	const cpp_int pow = states * states;
    for (cpp_int off = 1, no = pow, num = 1; off <= t; off += no, no *= pow, num *= pow)
		fm.addStep(genStep(t - off, num, states));

    return fm;
}

void
generateBoostGraph(const size_t& ni, const size_t& ns, const cpp_int& t,
	FlatMachine& fm, BoostGraph& bg)
{
    size_t stateCount = 0;
	fm.initials.reserve(ni);
    for (stateCount = 0; stateCount < ni; ++stateCount) {
		const string state{"s" + to_string(stateCount)};
		fm.initials.push_back(state);
		add_vertex(state, bg);
	}
	fm.states.reserve(ns);
	for (size_t i = 0; i < ns; ++i, ++stateCount) {
		const string state{"s" + to_string(stateCount)};
		fm.states.push_back(state);
		add_vertex(state, bg);
	}

	const cpp_int states = stateCount;
	const cpp_int pow = states * states;
    for (cpp_int off = 1, no = pow, num = 1; off <= t; off += no, no *= pow, num *= pow) {
		const FlatStep step{genStep(t - off, num, states)};
		fm.addStep(step);
		add_edge_by_label(step.source, step.target, bg);
	}
}

}
