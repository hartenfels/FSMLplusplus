#include "fsml/Machine.hpp"
#include "validator/Exception.hpp"
#include <algorithm>
#include <functional>
#include <unordered_set>
#include <boost/format.hpp>
namespace fsml
{ using namespace std; using boost::format;

Machine::Machine(const vector<string>& states, const string& initial,
		const vector<StepTup>& steps)
{
	for (const string& s : states)
		if (!stateMap.insert(pair<string, State>(s, State())).second)
			throw validator::Exception((format(validator::DISTINCT) % s).str());
	current = &stateMap.at(initial);
	for (const auto& s : steps)
		addStep(get<0>(s), get<1>(s), get<2>(s), get<3>(s));
	if (reachableFrom(current) < stateMap.size())
		throw validator::Exception(validator::REACHABLE);
}

Machine&
Machine::operator<<(const string& input)
{
    current = current->step(input);
	return *this;
}

const size_t
Machine::reachableFrom(const State* const start) const
{
    vector<const State*> left{start};
    unordered_set<const State*> reachable{start};
    left.reserve(stateMap.size());
	for (vector<const State*>::size_type i{0}; i < left.size(); ++i)
		for (const auto& stepPair : left[i]->getSteps()) {
			const State* target{stepPair.second.getTarget()};
			if (reachable.insert(target).second)
				left.push_back(target);
		}
	return left.size();
}

void
Machine::registerAt(const string& a, const ActionFunction& f)
{
	return actionMap.at(a).registerFunction(f);
}


void
Machine::addStep(const string& s, const string& i, const string& a,
		const string& t)
{
	State* const src{&stateMap.at(s)};
	State* const dst{t.empty() ? src : [&](){
				const auto it = stateMap.find(t);
				if (it == stateMap.end())
					throw validator::Exception(
							(format(validator::RESOLVABLE) % t % s).str());
				return &it->second;
			}()};
	if (!src->addStep(i, Step(dst, a.empty() ? nullptr : &actionMap[a])))
		throw validator::Exception(
				(format(validator::DETERMINISTIC) % i % s).str());
}

}
