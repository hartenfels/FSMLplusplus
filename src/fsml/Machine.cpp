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
	if (initials.size() != 1)
		throw InitialStateException{initials};
	current = &(*stateMap.insert({initials[0], State{initials[0]}}).first).second;
	for (const string& s : states)
		if (!stateMap.insert({s, State{s}}).second)
			throw UniqueException{s};
	for (const FlatStep& s : steps)
		addStep(s.source, s.input, s.action, s.target);
	const unordered_set<const State*> reachable{reachableFrom(current)};
	if (reachable.size() < stateMap.size())
		throw ReachableException{[&](){
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

const unordered_set<const State*>
Machine::reachableFrom(const State* const start) const
{
    vector<const State*> left{start};
    unordered_set<const State*> reachable{start};
    left.reserve(stateMap.size());
	for (vector<const State*>::size_type i{0}; i < left.size(); ++i)
		for (const auto& stepPair : left[i]->getSteps())
			if (reachable.insert(stepPair.second.getTarget()).second)
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
	if (!src->addStep(i, Step(dst, a.empty() ? nullptr : &actionMap[a])))
		throw DeterministicException{i, s};
}

}
