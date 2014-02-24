#include "fsml/Exceptions.hpp"
#include "fsml/Generator.hpp"
#include "test/GenerateTest.hpp"
#include "fsml/InputOutput.hpp"
#include "fsml/Machine.hpp"
#include "fsml/Parser.hpp"
#include <gtest/gtest.h>
#include <algorithm>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/visitors.hpp>
namespace fsml
{ using namespace std; using namespace boost; using namespace boost::multiprecision;

void
testConstraints()
{
	cout << "FSML++ Constraint Test\n";
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
testModel()
{
	cout << "FSML++ Model Test\n";
	const cpp_int maxT = 10000;
	for (size_t ns = 2; ns <= 19; ++ns) {
		cout << ns << " states...\n";
		for (cpp_int t = 0; t <= maxT; ++t) {
			FlatMachine fm1{generateFlatMachine(1, ns, t)};
			sort(fm1.states.begin(), fm1.states.end());
			sort(fm1.steps.begin(), fm1.steps.end());
			const AstMachine am1 = fm1;
			string s{generateFsml(am1)};
			const AstMachine am2 = parse<string::const_iterator>(s.begin(), s.end());
			const FlatMachine fm2{am2};
			ASSERT_EQ(am1, am2);
			ASSERT_EQ(fm1, fm2);
		}
	}
	cout << "Success.\n";
}

void
testMachine()
{
	cout << "FSML++ Machine Test\n";
	FlatMachine fm;
	BoostGraph graph;
	GraphMap gm;
	generateBoostGraph(1, 1, 12345, fm, graph, gm);

	vector<BoostGraph::vertex_descriptor> reachable;
	reachable.reserve(num_vertices(graph));
	breadth_first_search(graph.graph(), *vertices(graph).first,
			visitor(make_bfs_visitor(write_property(identity_property_map(),
			back_inserter(reachable), on_discover_vertex()))));

	if (reachable.size() == num_vertices(graph))
		ASSERT_NO_THROW(Machine{fm});
	else {
		sort(reachable.begin(), reachable.end());
		try {
			Machine{fm};
			FAIL();
		} catch(ReachableException& e) {
			sort(e.reachable.begin(), e.reachable.end());
			ASSERT_EQ(reachable.size(), e.reachable.size());
			for (size_t i = 0; i < reachable.size(); ++i)
				ASSERT_EQ(gm.at(reachable[i]), e.reachable[i]);
		}
	}

	cout << "Success.\n";
}

}

#define FSML_TEST_CONSTRAINTS 0
#define FSML_TEST_MODEL 0
#define FSML_TEST_MACHINE 1

int
main()
{
#if FSML_TEST_CONSTRAINTS
	fsml::testConstraints();
#endif
#if FSML_TEST_MODEL
	fsml::testModel();
#endif
#if FSML_TEST_MACHINE
	fsml::testMachine();
#endif
	return 0;
}

