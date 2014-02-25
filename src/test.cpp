#include "fsml/Exceptions.hpp"
#include "fsml/Generator.hpp"
#include "test/GenerateTest.hpp"
#include "fsml/InputOutput.hpp"
#include "fsml/Machine.hpp"
#include "fsml/Parser.hpp"
#include "test/BoostGraphBackInserter.hpp"
#include <algorithm>
#include <functional>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/lexical_cast.hpp>
#include <gtest/gtest.h>
namespace fsml
{ using namespace std; using namespace boost; using namespace boost::multiprecision;

static constexpr char RANGE[]{"Not enough arguments after argument %1%."};

void
testConstraints()
{
	cout << "\nFSML++ Constraint Test\n";
	ASSERT_NO_THROW(machineFromFile("tests/sample.fsml"));
	ASSERT_THROW(machineFromFile("tests/sample.fsml") << "foo", InvalidInputException);
	ASSERT_THROW(machineFromFile("tests/determinismNotOk.fsml"), DeterministicException);
	ASSERT_THROW(machineFromFile("tests/idsNotOk.fsml"), UniqueException);
	ASSERT_THROW(machineFromFile("tests/initialNotOk.fsml"), InitialStateException);
	ASSERT_THROW(machineFromFile("tests/missingFile.fsml"), FileReadException);
	ASSERT_THROW(machineFromFile("tests/parserError.fsml"), ParserException);
	ASSERT_THROW(machineFromFile("tests/reachabilityNotOk.fsml"), ReachableException);
	ASSERT_THROW(machineFromFile("tests/resolutionNotOk.fsml"), ResolvableException);
	cout << "Success.\n";
}

void
testModel(const size_t& ni, const size_t& ns, cpp_int t, const cpp_int& maxT)
{
	cout << "\nFSML++ Model Test"
			"\n........initial states: " << ni <<
 			"\n....non-initial states: " << ns <<
			"\n......transitions from: " << t.str() <<
			"\n........transitions to: " << maxT.str() <<
			"\n......transition count: " << cpp_int{1 + maxT - t}.str() << '\n';
	for (; t <= maxT; ++t) {
		FlatMachine fm1{generateFlatMachine(ni, ns, t)};
		sort(fm1.states.begin(), fm1.states.end());
		sort(fm1.steps.begin(), fm1.steps.end());
		const AstMachine am1 = fm1;
		string s{generateFsml(am1)};
		const AstMachine am2 = parse<string::const_iterator>(s.begin(), s.end());
		const FlatMachine fm2{am2};
		ASSERT_EQ(am1, am2);
		ASSERT_EQ(fm1, fm2);
	}
	cout << "Success.\n";
}

void
testMachine(const size_t& ns, cpp_int t, const cpp_int& maxT)
{
	cout << "\nFSML++ Machine Test"
 			"\n....non-initial states: " << ns <<
			"\n......transitions from: " << t.str() <<
			"\n........transitions to: " << maxT.str() <<
			"\n......transition count: " << cpp_int{1 + maxT - t}.str() << '\n';
	for (; t <= maxT; ++t) {
		FlatMachine fm1;
		BoostGraph bg;
		generateBoostGraph(1, ns, t, fm1, bg);

		vector<string> reachable;
		reachable.reserve(num_vertices(bg));
		breadth_first_search(bg.graph(), *vertices(bg).first,
				visitor(make_bfs_visitor(write_property(identity_property_map(),
				BoostGraphBackInserter{reachable}, on_discover_vertex()))));

		if (reachable.size() == num_vertices(bg)) {
			const Machine m{fm1};
			FlatMachine fm2{m};
			sort(fm1.states.begin(), fm1.states.end());
			sort(fm1.steps.begin(), fm1.steps.end());
			sort(fm2.states.begin(), fm2.states.end());
			sort(fm2.steps.begin(), fm2.steps.end());
			ASSERT_EQ(fm1, fm2);
		} else {
			sort(reachable.begin(), reachable.end());
			try {
				Machine{fm1};
				FAIL();
			} catch(ReachableException& e) {
				sort(e.reachable.begin(), e.reachable.end());
				ASSERT_EQ(reachable.size(), e.reachable.size());
				for (size_t i = 0; i < reachable.size(); ++i)
					ASSERT_EQ(reachable[i], e.reachable[i]);
			}
		}
	}
	cout << "Success.\n";
}

void
testSanity(const size_t& ni, const size_t& ns, cpp_int t)
{
	cout << "\nFSML++ Sanity Equality Check"
			"\n........initial states: " << ni <<
 			"\n....non-initial states: " << ns <<
			"\n............transition: " << t.str() << '\n';
	FlatMachine fm{generateFlatMachine(ni, ns, t)};
	ASSERT_EQ(fm, fm);
	const AstMachine am1 = fm;
	ASSERT_EQ(am1, am1);
	sort(fm.states.begin(), fm.states.end());
	sort(fm.steps.begin(), fm.steps.end());
	ASSERT_EQ(fm, fm);
	const AstMachine am2 = fm;
	ASSERT_EQ(am2, am2);
	cout << "Success.\n";
}

void
testSanity(const size_t& ni1, const size_t& ns1, cpp_int t1, const size_t& ni2,
	const size_t& ns2, cpp_int t2)
{
	cout << "\nFSML++ Sanity Inequality Check"
			"\n........initial states 1: " << ni1 <<
 			"\n....non-initial states 1: " << ns1 <<
			"\n............transition 1: " << t1.str() <<
			"\n........initial states 2: " << ni2 <<
 			"\n....non-initial states 2: " << ns2 <<
			"\n............transition 2: " << t2.str() << '\n';
	const FlatMachine fm1{generateFlatMachine(ni1, ns1, t1)},
			fm2{generateFlatMachine(ni2, ns2, t2)};
	ASSERT_NE(fm1, fm2);
	const AstMachine am1 = fm1, am2 = fm2;
	ASSERT_NE(am1, am2);
	cout << "Success.\n";
}

}


std::vector<std::function<void ()>>
parseArgs(const int& argc, char** argv)
{
	std::vector<std::function<void ()>> v;
	for (int i = 1; i < argc; ++i) {
		if (!strcmp(argv[i], "constraint"))
			v.push_back([](){fsml::testConstraints();});
		else if (!strcmp(argv[i], "model")) {
			if (argc <= i + 4)
				throw std::out_of_range{(boost::format(fsml::RANGE) % i).str()};
			const size_t ni{boost::lexical_cast<size_t>(argv[++i])},
					ns{boost::lexical_cast<size_t>(argv[++i])};
			const boost::multiprecision::cpp_int t{argv[++i]}, maxT{argv[++i]};
			v.push_back([=](){fsml::testModel(ni, ns, t, maxT);});
		} else if (!strcmp(argv[i], "machine")) {
			if (argc <= i + 3)
				throw std::out_of_range{(boost::format(fsml::RANGE) % i).str()};
			const size_t ns{boost::lexical_cast<size_t>(argv[++i])};
			const boost::multiprecision::cpp_int t{argv[++i]}, maxT{argv[++i]};
			v.push_back([=](){fsml::testMachine(ns, t, maxT);});
		} else if (!strcmp(argv[i], "sanityEqual")) {
			if (argc <= i + 3)
				throw std::out_of_range{(boost::format(fsml::RANGE) % i).str()};
			const size_t ni{boost::lexical_cast<size_t>(argv[++i])},
					ns{boost::lexical_cast<size_t>(argv[++i])};
			const boost::multiprecision::cpp_int t{argv[++i]};
			v.push_back([=](){fsml::testSanity(ni, ns, t);});
		} else if (!strcmp(argv[i], "sanityInequal")) {
			if (argc <= i + 6)
				throw std::out_of_range{(boost::format(fsml::RANGE) % i).str()};
			const size_t ni1{boost::lexical_cast<size_t>(argv[++i])},
					ns1{boost::lexical_cast<size_t>(argv[++i])};
			const boost::multiprecision::cpp_int t1{argv[++i]};
			const size_t ni2{boost::lexical_cast<size_t>(argv[++i])},
					ns2{boost::lexical_cast<size_t>(argv[++i])};
			const boost::multiprecision::cpp_int t2{argv[++i]};
			v.push_back([=](){fsml::testSanity(ni1, ns1, t1, ni2, ns2, t2);});
		} else
			throw std::invalid_argument{argv[i]};
	}
	return v;
}

int
main(int argc, char** argv)
{
	if (argc > 1)
		for (const auto& func : parseArgs(argc, argv))
			func();
	else
		std::cout <<
"FSML++ Test\n"
"Useage: fsmlpp_test TEST...\n"
"Tests:\n"
"  constraint                    Simple verification of the given constraints.\n"
"\n"
"  model <ni> <ns> <t> <maxT>    Identity testing of parser, abstract syntax\n"
"                                and flat representation.\n"
"\n"
"  machine <ns> <t> <maxT>       Oracle testing of machine against Boost's\n"
"                                directed graph and identity testing of flat\n"
"                                representation and actual machine.\n"
"\n"
"  sanityEqual <ni> <ns> <t>     Sanity check that compares a generated\n"
"                                flat representation and abstract syntax\n"
"                                against itself.\n"
"\n"
"  sanityInequal <ni1> <ns1>     Sanity check that compares the first flat\n"
"      <t1> <ni2> <ns2> <t2>     representation and abstract syntax against\n"
"                                the second one. Assuming the two given\n"
"                                configurations are different, they should\n"
"                                compare inequal."
"\n"
"Arguments:\n"
"  <ni>                          Number of initial states.\n"
"  <ns>                          Number of non-initial states.\n"
"  <t>                           Initial transition configuration.\n"
"  <maxT>                        Final transition configuration.\n";
	return 0;
}

