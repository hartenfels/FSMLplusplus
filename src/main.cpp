#include "fsml/FlatMachine.hpp"
#include "fsml/Generator.hpp"
#include "fsml/InputOutput.hpp"
#include "fsml/Parser.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <boost/xpressive/xpressive.hpp>

int
main(int argc, const char* argv[])
{
	using namespace std; using namespace fsml; using namespace boost::xpressive;
	cout << "FSML++\n";
	if (argc != 2)
		cout << "USAGE: fsmlpp SOURCE\n";
	else {
		const string fileArg{argv[1]};
		cout << "Opening " << fileArg << "...";
		const string s{readFile(fileArg)};
		cout << "OK\nParsing...";
		const FlatMachine fm{parse<string::const_iterator>(s.begin(), s.end(), fileArg)};
		cout << "OK\nValidating...";
		Machine machine{fm.initials, fm.states, fm.steps};
		cout << "OK\nGenerating:\n";
		const string i{regex_replace(fileArg, sregex{~alpha}, string{})};
		cout << '\t' << i << ".hpp...";
		ofstream(i + ".hpp") << generateCode(i, s, fm);
/*		cout << "OK\n\t" << i << ".tex...";

		auto it = find_if_not(am.states.begin(), am.states.end(),
				[](const ast::State& s){return s.initial.empty();});
		vector<string> st;
		st.reserve(am.states.size() - 1);
		for_each(am.states.begin(), it, [&](const ast::State& s){st.push_back(s.id);});
		for_each(next(it), am.states.end(), [&](const ast::State& s){st.push_back(s.id);});
		vector<StepTup> self, other;
		for (const ast::State& asta : am.states)
			for (const ast::Step& aste : asta.steps)
				if (aste.target.empty() || aste.target == asta.id)
					self.push_back(StepTup(asta.id, aste.input, aste.action, asta.id));
				else
					other.push_back(StepTup(asta.id, aste.input, aste.action, aste.target));

		ofstream(i + ".tex") << generateLatex(it->id, st, self, other);*/
		cout << "OK\nDone.\n";
	}
	return 0;
}

