#include "generate/Generator.hpp"
#include "parser/State.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/format.hpp>
namespace fsml
{ using namespace std; using boost::format;
namespace karma = boost::spirit::karma;
namespace fsmlcs = boost::spirit::ascii;

const string HPP{fileToString("hpp.template")};
const string CPP{fileToString("cpp.template")};
const string LATEX{fileToString("latex.template")};
constexpr char STATE[]{"\t\t\"%1%\",\n"};
constexpr char STEP[]{"\t\tStepTup(\"%1%\", \"%2%\", \"%3%\", \"%4%\"),\n"};
constexpr char NODE[]
		{"\\node[state](%1%)[right of=%2%]{\\parbox{1.5cm}{\\centering %1%}};"};
constexpr char SELF[]{"(%1%)edge[loop]node{%2%}(%1%)"};
constexpr char OTHER[]{"(%1%)edge[bend left]node{%2%}(%3%)"};

string
fileToString(const string& file)
{
	stringstream ss;
	ifstream stream(file);
	if (!stream)
		throw 0;
	ss << stream.rdbuf();
	return ss.str();
}

const string
generateHeader(const string& identifier, const string& fsmlCode)
{
	return (format(HPP) % identifier % fsmlCode).str();
}

const string
generateSource(const string& identifier, const FlatMachine& fm)
{
	string states, steps;
	karma::generate(back_insert_iterator<string>(states),
			*("\t\t\"" << +fsmlcs::alpha << "\",\n"), fm.states);
	const vector<string> v(fm.steps.begin(), fm.steps.end());
	karma::generate(back_insert_iterator<string>(steps),
			*("\t\t" << +karma::char_ << ",\n"), v);
	return (format(CPP) % identifier % (format(STATE) %	fm.initials[0]) %
			states % steps).str();
}

const string
generateLatex(const string& init, const vector<string>& states,
	const vector<StepTup>& self, const vector<StepTup>& other)
{
	const string* prev{&init};
	stringstream ss1, ss2;
	for (const string& s : states) {
		ss1 << (format(NODE) % s % *prev).str() << '\n';
		prev = &s;
	}
	for (const StepTup& tup : self)
		ss2 << (format(SELF) % get<0>(tup) % get<1>(tup)).str() << '\n';
	for (const StepTup& tup : other)
		ss2 << (format(OTHER) % get<0>(tup) % get<1>(tup) %
				get<3>(tup)).str() << '\n';
	return (format(LATEX) % (5 + states.size() * 5) % (6 + states.size()) % init % ss1.str() %
			ss2.str()).str();
}

}
