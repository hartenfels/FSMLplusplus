#include "generate/Generator.hpp"
#include "parser/State.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/format.hpp>
namespace fsml
{ using namespace std; using boost::format;

const string HPP{fileToString("hpp.template")};
const string CPP{fileToString("cpp.template")};
constexpr char INITIAL[]{"\"%1%\""};
constexpr char STATE[]{"\t\t\t\"%1%\",\n"};
constexpr char STEP[]{"\t\t\tStepTup(\"%1%\", \"%2%\", \"%3%\", \"%4%\"),\n"};

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

template<typename T, size_t N> string
formatVector(const vector<T>& v, const std::string& tmpl,
		array<const function<string (const T&)>, N> funcs)
{
    if (v.empty())
		return "";
	stringstream ss;
	for (const T& s : v) {
		format form{tmpl};
		for (const function<string (const T&)> f : funcs)
			form % f(s);
		ss << form.str();
	}
	return ss.str();
}

static const vector<StepTup>
steps(const vector<ast::State>& sts)
{
    vector<StepTup> steps;
	for (const auto& sta : sts)
		for (const auto& ste : sta.steps)
            steps.push_back(StepTup(sta.id, ste.input, ste.action, ste.target));
    return steps;
}

const string
generateHeader(const string& identifier, const string& fsmlCode)
{
	return (format(HPP) % identifier % fsmlCode).str();
}

const std::string
generateSource(const string& identifier, const ast::Machine& am)
{
	// Magic. TODO: make less magic, probably via a better abstract syntax.
	return (format(CPP) % identifier % formatVector<ast::State, 1>(am.states,
			STATE, {{[](const ast::State& st){return st.id;}}}) %
			(format(INITIAL) % find_if_not(am.states.begin(), am.states.end(),
			[](const ast::State& s){return s.initial.empty();})->id) %
			formatVector<StepTup, 4>(steps(am.states), STEP,
			{{[](const StepTup& st){return get<0>(st);},
			[](const StepTup& st){return get<1>(st);},
			[](const StepTup& st){return get<2>(st);},
			[](const StepTup& st){return get<3>(st).empty() ? get<0>(st) :
			get<3>(st);}}})).str();
}

}
