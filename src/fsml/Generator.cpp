#include "fsml/Generator.hpp"
#include "fsml/InputOutput.hpp"
#include <sstream>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/spirit/include/karma.hpp>
namespace fsml
{using namespace std; using boost::format; using boost::to_upper_copy;
namespace karma = boost::spirit::karma;

// Templates for C++
static const string CODE{readFile("templates/hpp.template")};
static constexpr char STATE[]{"\t\t\t\"%1%\",\n"};
// Templates for LaTeX
static const string LATEX{readFile("templates/latex.template")};
static constexpr char NODE[]
		{"\\node[state](%1%)[right of=%2%]{\\parbox{1.5cm}{\\centering %1%}};\n"};
static constexpr char SELF[]
		{"(%1%)edge[loop]node{\\parbox{1cm}{\\centering %2%}}(%3%)\n"};
static constexpr char OTHER[]
		{"(%1%)edge[bend left]node{\\parbox{1cm}{\\centering %2%}}(%3%)\n"};
// Templates for Graphviz
static const string DOT{readFile("templates/dot.template")};
static constexpr char ARROW[]{"\t%1% -> %2% [label=\" %3% \"];\n"};

const string
generateFsml(const AstMachine& am)
{
	stringstream ss;
	for (const AstState& state : am.states) {
		if (!state.initial.empty())
			ss << state.initial << ' ';
		ss << "state " << state.id << " {\n";
		for (const AstStep& step : state.steps) {
			ss << "  " << step.input;
			if (!step.action.empty())
				ss << '/' << step.action;
			if (!step.target.empty())
				ss << " -> " << step.target;
			ss << ";\n";
		}
		ss << "}\n";
	}
	return ss.str();
}

const string
generateCode(const string& name, const FlatMachine& fm)
{
	string states, steps;
	// Convert vector of FlatStates to vector of string
	const vector<string> v(fm.steps.begin(), fm.steps.end());
	// Use Karma to fill string with states...
	karma::generate(back_insert_iterator<string>(states),
			*("\t\t\t\"" << +karma::char_ << "\",\n"), fm.states);
	// ...and transitions
	karma::generate(back_insert_iterator<string>(steps),
			*("\t\t\t" << +karma::char_ << ",\n"), v);
	return (format(CODE) % to_upper_copy(name) % generateFsml(fm) % name %
			(format(STATE) % *fm.initials.cbegin()) % states % steps).str();
}

const string
generateLatex(const FlatMachine& fm)
{
	size_t paperWidth = (fm.states.size() + 1) * 5, paperHeight = 6 + fm.states.size();
	// Nodes
	// rightOf is needed to tell the nodes their position
	const string* rightOf{&*fm.initials.cbegin()};
	stringstream nodes;
	for (const string& s : fm.states) {
		nodes << (format(NODE) % s % *rightOf).str();
		rightOf = &s;
	}
	// Paths
	stringstream paths;
	for (auto it = fm.stepMap.begin(); it != fm.stepMap.end(); it = next(it)) {
        string transition;
		karma::generate(back_insert_iterator<string>(transition),
			*("\\contour{white}{" << +karma::char_ << "} "), it->second);
		// Depending on if source and target being identical, we need different templates
		paths << ((it->first.first == it->first.second ? format(SELF) : format(OTHER)) %
				it->first.first % transition % it->first.second).str();
	}
	return (format(LATEX) % paperWidth % paperHeight % *fm.initials.cbegin() %
			nodes.str() % paths.str()).str();
}

const string
generateDot(const string& name, const FlatMachine& fm)
{
	stringstream arrows;
	for (const FlatStep& fs : fm.steps)
		arrows << (format(ARROW) % fs.source % fs.target % fs.getStepText()).str();
	return (format(DOT) % name % *fm.initials.cbegin() % arrows.str()).str();
}

}
