#include "fsml/Machine.hpp"
#include "fsml/Exceptions.hpp"
#include <algorithm>
#include <functional>
#include <boost/format.hpp>
namespace fsml
{ using namespace std; using boost::format;

Machine::Machine(const FlatMachine& fm) :
	Machine(fm.initials, fm.states, fm.steps) {}

Machine::Machine(const vector<string>& initials, const vector<string>& states,
		const vector<FlatStep>& steps)
{
	// The initials vector must have exactly one state, which is the initial state
	if (initials.size() != 1)
		throw InitialStateException{initials};
	// Insert initial state and set current state to it
	current = &(*stateMap.insert({*initials.cbegin(),
			State{*initials.cbegin(), true}}).first).second;
	// Add all other states, throw on duplicate
	for (const string& s : states)
		if (!stateMap.insert({s, State{s}}).second)
			throw UniqueException{s};
	// Add all steps
	for (const FlatStep& s : steps)
		addStep(s.source, s.input, s.action, s.target);
	// Gather states reachable from the initial (current) state
	const unordered_set<const State*> reachable{reachableFrom(current)};
	if (reachable.size() < stateMap.size())
		throw ReachableException{[&](){
			// Collect unreachable states for error message via reachable \ stateMap
			vector<string> unreachable;
			for (const auto& p : stateMap)
				if (reachable.find(&p.second) == reachable.end())
					unreachable.push_back(p.second.getId());
			return unreachable;
		}()};
}

Machine&
Machine::operator<<(const string& input)
{
    current = current->step(input);
	return *this;
}

Machine::operator FlatMachine() const
{
    FlatMachine fm;
	for (const pair<string, State>& p : stateMap) {
		(p.second.isInitial() ? fm.initials : fm.states).push_back(p.first);
		for (const pair<string, Step>& step : p.second.getSteps()) {
			const Action* const action{step.second.getAction()};
			fm.addStep({p.first, step.first, action ? action->getId() : string{},
					step.second.getTarget()->getId()});
		}
	}
    return fm;
}

const unordered_set<const State*>
Machine::reachableFrom(const State* const start) const
{
    vector<const State*> left{start};
    unordered_set<const State*> reachable{start};
    left.reserve(stateMap.size());
    // Iterate through the left, which grows as more reachable states are found
	for (vector<const State*>::size_type i{0}; i < left.size(); ++i)
		// Iterate through all transitions of each reachable state
		for (const auto& stepPair : left[i]->getSteps())
			// All targets of reachable states are reachable
			if (reachable.insert(stepPair.second.getTarget()).second)
				// If the state wasn't reachable already, add it to left to be processed
				left.push_back(stepPair.second.getTarget());
	return reachable;
}

void
Machine::registerAt(const string& a, const ActionFunction& f)
{
	return actionMap.at(a).registerFunction(f);
}

const State&
Machine::getCurrentState() const
{
	return *current;
}


void
Machine::addStep(const string& s, const string& i, const string& a,
		const string& t)
{
	State* const src{&stateMap.at(s)};
	State* const dst{[&](){
		const auto it = stateMap.find(t);
		if (it == stateMap.end())
			throw ResolvableException{t, s};
		return &it->second;
	}()};
	if (!src->addStep(i, {dst, a.empty() ? nullptr :
			// Insert action, if it does not yet exist, and get a pointer to the value
			&actionMap.insert({a, {a}}).first->second}))
		throw DeterministicException{i, s};
}

}
