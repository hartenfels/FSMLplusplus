#include "validator/Validator.hpp"
#include "validator/Exception.hpp"
#include "fsml/State.hpp"
#include <boost/format.hpp>
#include <algorithm>
#include <vector>
namespace fsml { namespace validator
{ using namespace std; using boost::format;

static const vector<string>
ids(const vector<ast::State>& sts)
{
	vector<string> ids;
	ids.reserve(sts.size());
	transform(sts.begin(), sts.end(), back_inserter(ids),
			[](const ast::State& s){return s.id;});
	return ids;
}

static const string&
initial(const vector<ast::State>& sts)
{
	static const auto func = [](const ast::State& s){return s.initial.empty();};
	auto init = find_if_not(sts.begin(), sts.end(), func);
	if (init == sts.end())
		throw Exception(NO_INITIAL);
	auto otherInit = find_if_not(next(init), sts.end(), func);
	if (otherInit != sts.end())
		throw Exception((format(INITIALS) % init->id % otherInit->id).str());
	return init->id;
}

static const vector<StepTup>
steps(const vector<ast::State>& sts)
{
    vector<StepTup> steps;
	for (const ast::State& sta : sts) {
		for (const ast::Step& ste : sta.steps) {
            steps.push_back(StepTup(sta.id, ste.input, ste.action, ste.target));
		}
	}
    return steps;
}

Machine
validate(const ast::Machine& am)
{
	return Machine(ids(am.states), initial(am.states), steps(am.states));
}

}}
