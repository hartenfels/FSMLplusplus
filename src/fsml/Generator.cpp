#include "fsml/Generator.hpp"
#include "fsml/InputOutput.hpp"
#include <sstream>
#include <tuple>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/spirit/include/karma.hpp>
namespace fsml
{using namespace std; using boost::format; using boost::to_upper_copy;
namespace karma = boost::spirit::karma; namespace fsmlcs = boost::spirit::ascii;

static const string CODE{readFile("hpp.template")};
static constexpr char STATE[]{"\t\t\"%1%\",\n"};
static constexpr char STEP[]{"\t\tStepTup(\"%1%\", \"%2%\", \"%3%\", \"%4%\"),\n"};
static const string LATEX{readFile("latex.template")};
static constexpr char NODE[]
		{"\\node[state](%1%)[right of=%2%]{\\parbox{1.5cm}{\\centering %1%}};\n"};
static constexpr char SELF[]
		{"(%1%)edge[loop]node{\\parbox{1cm}{\\centering %2%}}(%3%)\n"};
static constexpr char OTHER[]
		{"(%1%)edge[bend left]node{\\parbox{1cm}{\\centering %2%}}(%3%)\n"};
static const string DOT{readFile("dot.template")};
static constexpr char ARROW[]{"\t%1% -> %2% [label=\" %3% \"];\n"};

const string
generateCode(const string& name, const string& fsmlCode, const FlatMachine& fm)
{
	string states, steps;
	const vector<string> v(fm.steps.begin(), fm.steps.end());
	karma::generate(back_insert_iterator<string>(states),
			*("\t\t\"" << +fsmlcs::alpha << "\",\n"), fm.states);
	karma::generate(back_insert_iterator<string>(steps),
			*("\t\t" << +karma::char_ << ",\n"), v);
	return (format(CODE) % to_upper_copy(name) % fsmlCode % name %
			(format(STATE) % fm.initials.at(0)) % states % steps).str();
}

const string
generateLatex(const FlatMachine& fm)
{
	size_t paperWidth = (fm.states.size() + 1) * 5, paperHeight = 6 + fm.states.size();
	// Nodes
	const string* rightOf{&fm.initials.at(0)};
	stringstream nodes;
	for (const string& s : fm.states) {
		nodes << (format(NODE) % s % *rightOf).str();
		rightOf = &s;
	}
	// Paths
	stringstream paths;
	for (auto it = fm.stepMap.begin(); it != fm.stepMap.end(); it = next(it)) {
        stringstream transition;
        for (const FlatStep& fs : it->second)
			transition << "\\contour{white}{" << fs.getStepText() << "} ";
		paths << ((it->first.first == it->first.second ? format(SELF) : format(OTHER)) %
				it->first.first % transition.str() % it->first.second).str();
	}
	return (format(LATEX) % paperWidth % paperHeight % fm.initials[0] % nodes.str() %
			paths.str()).str();
}

const string
generateDot(const string& name, const FlatMachine& fm)
{
	stringstream arrows;
	for (const FlatStep& fs : fm.steps)
		arrows << (format(ARROW) % fs.source % fs.target % fs.getStepText()).str();
	return (format(DOT) % name % fm.initials.at(0) % arrows.str()).str();
}

}
