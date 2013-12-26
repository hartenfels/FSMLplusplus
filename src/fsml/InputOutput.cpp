#include "fsml/InputOutput.hpp"
#include "fsml/Exceptions.hpp"
#include "parser/Parser.hpp"
#include <fstream>
#include <sstream>
namespace fsml { namespace io
{ using namespace std;

string
readFile(const string& file)
{
	stringstream ss;
	ifstream stream(file);
	if (!stream)
		throw exception::FileReadException{file};
	ss << stream.rdbuf();
	return ss.str();
}

Machine
machineFromFile(const string& f)
{
	const string s{readFile(f)};
	return Machine{parser::parse<string::const_iterator>(s.begin(), s.end(), f)};
}

}}
