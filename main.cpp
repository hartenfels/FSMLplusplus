#include "parser/Parser.hpp"
#include "parser/NewParser.hpp"
#include "validator/Validator.hpp"
#include "generate/Generator.hpp"
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

int
main(int argc, const char* argv[])
{
	using namespace std;
	using namespace fsml;
	cout << "FSML++\n";
	if (argc != 2)
		cout << "USAGE: fsmlpp SOURCE\n";
	else {
		cout << "Opening " << argv[1] << "...";
		const string s{fsml::fileToString(argv[1])};
		cout << "OK\nParsing...";
		const ast::Machine am = parser::parse<string::const_iterator>(s.begin(), s.end());
		cout << "OK\nValidating...";
		Machine machine{validator::validate(am)};
		cout << "OK\nGenerating:\n";
		const string i{to_string(time(nullptr))};
		cout << "\tMachine" << i << ".hpp...";
		ofstream("Machine" + i + ".hpp") << generateHeader(i, s);
		cout << "OK\n\tMachine" << i << ".cpp...";
		ofstream("Machine" + i + ".cpp") << generateSource(i, am);
		cout << "OK\nDone.\n";
	}
}

