#include "fsml/Exceptions.hpp"
#include "fsml/InputOutput.hpp"
#include "fsml/Generator.hpp"
#include "fsml/Parser.hpp"
#include "test/GenerateTest.hpp"
#include <gtest/gtest.h>

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
	cout << "t\t\tstep 1\t\tstep 2\t\tstep 3\n";
	for (cpp_int t = 0; t <= 84; ++t) {
		vector<FlatStep> v;
		const FlatMachine fm = geno(1, 1, t, v);
		cout << t;
		for (const FlatStep& fs : v)
			cout << "\t\t" << fs.source << " > " << fs.target;
		cout << '\n';
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

