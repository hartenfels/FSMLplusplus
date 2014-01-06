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
		Machine machine{fm};
		cout << "OK\nGenerating:\n";
		const string i{regex_replace(fileArg, sregex{~alpha}, string{})};
		cout << '\t' << i << ".hpp...";
		ofstream(i + ".hpp") << generateCode(i, s, fm);
		cout << "OK\n\t" << i << ".tex...";
		ofstream(i + ".tex") << generateLatex(fm);
		cout << "OK\n\t" << i << ".dot...";
		ofstream(i + ".dot") << generateDot(i, fm);
		cout << "OK\nDone.\n";
	}
	return 0;
}

