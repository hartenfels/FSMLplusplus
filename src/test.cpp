#include "fsml/Exceptions.hpp"
#include "fsml/InputOutput.hpp"
#include <gtest/gtest.h>

void
fsmlppTest(int& result)
{
	using namespace fsml;
	result = 1;
	ASSERT_NO_THROW(machineFromFile("tests/sample.fsml"));
	++result;
	ASSERT_THROW(machineFromFile("tests/sample.fsml") << "foo", InvalidInputException);
	++result;
	ASSERT_THROW(machineFromFile("tests/determinismNotOk.fsml"), DeterministicException);
	++result;
	ASSERT_THROW(machineFromFile("tests/idsNotOk.fsml"), UniqueException);
	++result;
	ASSERT_THROW(machineFromFile("tests/initialNotOk.fsml"), InitialStateException);
	++result;
	ASSERT_THROW(machineFromFile("tests/missingFile.fsml"), FileReadException);
	++result;
	ASSERT_THROW(machineFromFile("tests/parserError.fsml"), ParserException);
	++result;
	ASSERT_THROW(machineFromFile("tests/reachabilityNotOk.fsml"), ReachableException);
	++result;
	ASSERT_THROW(machineFromFile("tests/resolutionNotOk.fsml"), ResolvableException);
	result = 0;
}

int
main()
{
	using namespace std;
	cout << "FSML++ Unit Test\n";
	int result;
	fsmlppTest(result);
	if (result)
		cout << "Done, error in test #" << result << ".\n";
	else
		cout << "Done, no errors.\n";
	return result;
}

