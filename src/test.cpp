#include "fsml/Exceptions.hpp"
#include "fsml/InputOutput.hpp"
#include <gtest/gtest.h>

int
main()
{
	using namespace std; using namespace fsml::io; using namespace fsml::exception;
	EXPECT_NO_THROW(machineFromFile("tests/sample.fsml"));
	EXPECT_THROW(machineFromFile("tests/sample.fsml") << "foo", InvalidInputException);
	EXPECT_THROW(machineFromFile("tests/determinismNotOk.fsml"), DeterministicException);
	EXPECT_THROW(machineFromFile("tests/idsNotOk.fsml"), UniqueException);
	EXPECT_THROW(machineFromFile("tests/initialNotOk.fsml"), InitialStateException);
	EXPECT_THROW(machineFromFile("tests/missingFile.fsml"), FileReadException);
	EXPECT_THROW(machineFromFile("tests/parserError.fsml"), ParserException);
	EXPECT_THROW(machineFromFile("tests/reachabilityNotOk.fsml"), ReachableException);
	EXPECT_THROW(machineFromFile("tests/resolutionNotOk.fsml"), ResolvableException);
	return 0;
}

