#include "fsml/InputOutput.hpp"
#include "fsml/Exceptions.hpp"
#include "fsml/Parser.hpp"
#include <fstream>
#include <sstream>
namespace fsml
{ using namespace std;

string
readFile(const string& file)
{
	stringstream ss;
	ifstream stream(file);
	if (!stream)
		throw FileReadException{file};
	ss << stream.rdbuf();
	return ss.str();
}

Machine
machineFromFile(const string& f)
{
	const string s{readFile(f)};
	return Machine{parse<string::const_iterator>(s.begin(), s.end(), f)};
}

}
