#include "parser/Parser.hpp"
#include "parser/NewParser.hpp"
#include "parser/FlatMachine.hpp"
#include "generate/Generator.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <boost/xpressive/xpressive.hpp>

/*int
miin()
{
	using namespace std; using namespace fsml;
	const string s{fileToString("sample.fsml")};
	parser::newParse<string::const_iterator>(s.begin(), s.end());
	return 0;
}

int
muin()
{
	using namespace std; using namespace fsml;
	const string s{fileToString("sample.fsml")};
	const ast::Machine am(parser::parse<string::const_iterator>(s.begin(),
			s.end()));
	Machine m{validator::validate(am)};
	vector<string> ids;
	ids.reserve(am.states.size());
	transform(am.states.begin(), am.states.end(), back_inserter(ids),
			[](const ast::State& s){return s.id;});
	std::string generated;
	std::back_insert_iterator<std::string> sink(generated);
	if (!generateKarma(sink, "SampleFsml", ids))
		throw 0;
	cout << generated;
	return 0;
}*/

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
		const string s{fileToString(fileArg)};
		cout << "OK\nParsing...";
		const FlatMachine fm{parser::parse<string::const_iterator>(s.begin(), s.end(), fileArg)};
		cout << "OK\nValidating...";
		Machine machine{fm.initials, fm.states, fm.steps};
		cout << "OK\nGenerating:\n";
		const string i{regex_replace(fileArg, sregex{~alpha}, string{})};
		cout << '\t' << i << ".hpp...";
		ofstream(i + ".hpp") << generateHeader(i, s);
		cout << "OK\n\t" << i << ".cpp...";
		ofstream(i + ".cpp") << generateSource(i, fm);
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

