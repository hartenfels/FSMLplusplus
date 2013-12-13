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
		const string s{fsml::fileToString(argv[1])};
		const ast::Machine am = parser::parse<string::const_iterator>(s.begin(), s.end());
		Machine machine{validator::validate(am)};
		const string i{to_string(time(nullptr))};
		ofstream("Machine" + i + ".hpp") << generateHeader(i, s);
		ofstream("Machine" + i + ".cpp") << generateSource(i, am);
	}
}

