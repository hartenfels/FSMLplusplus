#include "fsml/Exceptions.hpp"
#include "fsml/InputOutput.hpp"
#include "fsml/Generator.hpp"
#include "fsml/Parser.hpp"
#include "test/GenerateTest.hpp"
#include <gtest/gtest.h>
#include <algorithm>

int
main()
{
	using namespace std; using namespace fsml; using namespace boost::multiprecision;
	cout << "FSML++ Unit Test\n";
	EXPECT_NO_THROW(machineFromFile("tests/sample.fsml"));
	EXPECT_THROW(machineFromFile("tests/sample.fsml") << "foo", InvalidInputException);
	EXPECT_THROW(machineFromFile("tests/determinismNotOk.fsml"), DeterministicException);
	EXPECT_THROW(machineFromFile("tests/idsNotOk.fsml"), UniqueException);
	EXPECT_THROW(machineFromFile("tests/initialNotOk.fsml"), InitialStateException);
	EXPECT_THROW(machineFromFile("tests/missingFile.fsml"), FileReadException);
	EXPECT_THROW(machineFromFile("tests/parserError.fsml"), ParserException);
	EXPECT_THROW(machineFromFile("tests/reachabilityNotOk.fsml"), ReachableException);
	EXPECT_THROW(machineFromFile("tests/resolutionNotOk.fsml"), ResolvableException);
	cout << "Done.\n";

	cout << "FSML++ Generative Test\n";
	const cpp_int maxT = 10000;
	for (size_t ns = 2; ns <= 19; ++ns) {
		cout << ns << ":\n";
		for (cpp_int t = 0; t <= maxT; ++t) {
			FlatMachine fm1{geno(1, ns, t)};
			sort(fm1.states.begin(), fm1.states.end());
			sort(fm1.steps.begin(), fm1.steps.end());
			const AstMachine am1 = fm1;
			string s{generateFsml(am1)};
			const AstMachine am2 = parse<string::const_iterator>(s.begin(), s.end());
			const FlatMachine fm2{am2};
			EXPECT_EQ(am1, am2);
			EXPECT_EQ(fm1, fm2);
		}
	}
/*
	AstMachine am = fm;
	string s = generateFsml(am);
	cout << s;
	AstMachine am2 = parse<string::const_iterator>(s.begin(), s.end(), "test");
    FlatMachine fm2 = am2;
    EXPECT_EQ(am, am2);
    EXPECT_EQ(fm, fm2);
*/
	cout << "Done.\n";
	return 0;
}

