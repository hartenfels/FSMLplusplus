#include "parser/Parser.hpp"
#include "parser/NewParser.hpp"
#include "validator/Validator.hpp"
#include "generate/Generator.hpp"
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
		const string s{fsml::fileToString(fileArg)};
		cout << "OK\nParsing...";
		const ast::Machine am(parser::parse<string::const_iterator>(s.begin(),
				s.end()));
		cout << "OK\nValidating...";
		Machine machine{validator::validate(am)};
		cout << "OK\nGenerating:\n";
		const string i{regex_replace(fileArg, sregex{~alpha}, string{})};
		cout << '\t' << i << ".hpp...";
		ofstream(i + ".hpp") << generateHeader(i, s);
		cout << "OK\n\t" << i << ".cpp...";
		ofstream(i + ".cpp") << generateSource(i, am);
		cout << "OK\nDone.\n";
		cout << generateLatex(i, am);
	}
}

