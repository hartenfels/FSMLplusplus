#include "fsml/InputOutput.hpp"
#include "fsml/Exceptions.hpp"
#include "fsml/Parser.hpp"
#include <fstream>
#include <sstream>
namespace fsml
{ using namespace std;

string
readFile(const string& f)
{
	stringstream ss;
	ifstream stream(f);
	if (!stream)
		throw FileReadException{f};
	ss << stream.rdbuf();
	return ss.str();
}

void
writeFile(const string& f, const string& c)
{
	ofstream out{f};
	out << c;
	if (!out)
		throw FileWriteException{f};
}

Machine
machineFromFile(const string& f)
{
	const string s{readFile(f)};
	return Machine{parse<string::const_iterator>(s.begin(), s.end(), f)};
}

}
