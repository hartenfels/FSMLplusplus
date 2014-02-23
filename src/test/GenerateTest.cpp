#include "GenerateTest.hpp"
#include "fsml/Machine.hpp"
#include "fsml/Exceptions.hpp"
namespace fsml
{ using namespace std; using namespace boost::multiprecision;

static FlatStep
genStep(const cpp_int& pos, const cpp_int& num,
		const cpp_int& states)
{
	const cpp_int source = (pos / num) % states;
	const cpp_int target = (pos / (num * states)) % states;
	return {"s" + source.str(), "input" + pos.str(), "", "s" + target.str()};
}


FlatMachine
geno(const size_t& ni, const size_t& ns, const cpp_int& t)
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
genoTest()
{
	for (size_t ns = 2; ns <= 9; ++ns) {
		cout << ns << ": ";
		for (cpp_int t = 0; t <= 10000; ++t) {
			try {
				Machine{geno(1, ns, t)};
				cout << t << ' ';
			} catch(ReachableException& e) {
			}
		}
		cout << '\n';
	}
	/*
	cout << "t\t\tstep 1\t\tstep 2\t\tstep 3\n";
	for (cpp_int t = 0; t <= MAX_T; ++t) {
		vector<FlatStep> v;
		const FlatMachine fm = geno(1, NORMAL_STATES, t, v);
		cout << t;
		for (const FlatStep& fs : v)
			cout << "\t\t" << fs.source << " > " << fs.target;
		cout << '\n';
	}
	*/
}

}
