#ifndef FSML_EXCEPTIONS_HPP
#define FSML_EXCEPTIONS_HPP
#include <stdexcept>
#include <set>
#include <vector>
namespace fsml
{
/**@file Contains all exceptions used in FSML++.*/

/**Exception thrown if input in State is not deterministic.*/
struct DeterministicException : std::runtime_error
{
	DeterministicException(const std::string& input, const std::string& state);
};

/**Exception thrown if an error occurs reading from a file.*/
struct FileReadException : std::runtime_error
{
	FileReadException(const std::string& file);
};

/**Exception thrown if an error occurs writing to a file.*/
struct FileWriteException : std::runtime_error
{
	FileWriteException(const std::string& file);
};

/**Exception thrown if a Machine constructs with more or less than one initial state.*/
struct InitialStateException : std::runtime_error
{
	InitialStateException(const std::vector<std::string>& states);
};

/**Exception thrown if an invalid input is fed into a Machine.*/
struct InvalidInputException : std::runtime_error
{
	InvalidInputException(const std::string& state, const std::string& input);
};

/**Exception thrown if parsing fails.*/
struct ParserException : std::runtime_error
{
	ParserException(const std::string& file);
};

/**Exception thrown if not all States in a Machine are reachable.*/
struct ReachableException : std::runtime_error
{
	ReachableException(const std::pair<std::vector<std::string>,
		std::vector<std::string>>& states);
	std::vector<std::string> reachable;
};

/**Exception thrown if the target of a Step is not resolvable.*/
struct ResolvableException : std::runtime_error
{
	ResolvableException(const std::string& target, const std::string& state);
};

/**Exception thrown if a State's name in a Machine is not unique.*/
struct UniqueException : std::runtime_error
{
	UniqueException(const std::string& state);
};

}
#endif // FSML_EXCEPTIONS_HPP
