#include "GenerateTest.hpp"
namespace fsml
{ using namespace std; using namespace boost::multiprecision;

static FlatStep
genStep(const cpp_int pos, const cpp_int num,
		const cpp_int& states)
{
	const cpp_int source = (pos / num) % states;
	const cpp_int target = (pos / (num * states)) % states;
	return {"s" + source.str(), "input", "", "s" + target.str()};
}


FlatMachine
geno(const size_t& ni, const size_t& ns, const cpp_int& t, vector<FlatStep>& v)
{
    FlatMachine fm;
    size_t stateCount = 0;
    for (stateCount = 0; stateCount < ni; ++stateCount)
		fm.initials.insert("s" + to_string(stateCount));
	for (size_t i = 0; i < ns; ++i, ++stateCount)
		fm.states.insert("s" + to_string(stateCount));

	const cpp_int states = stateCount;
	const cpp_int pow = states * states;
    for (cpp_int off = 1, no = pow, num = 1; off <= t; off += no, no *= pow, num *= pow) {
		FlatStep fs = genStep(t - off, num, states);
		fm.steps.insert(fs);
		v.push_back(fs);
	}

    return fm;
}

}
