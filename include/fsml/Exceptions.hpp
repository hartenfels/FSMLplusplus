#ifndef FSML_EXCEPTIONS_HPP
#define FSML_EXCEPTIONS_HPP
#include <stdexcept>
#include <vector>
namespace fsml
{

struct DeterministicException : std::runtime_error
{
	DeterministicException(const std::string& input, const std::string& state);
	virtual ~DeterministicException() noexcept = default;
};

struct FileReadException : std::runtime_error
{
	FileReadException(const std::string& file);
	virtual ~FileReadException() noexcept = default;
};

struct InitialStateException : std::runtime_error
{
	InitialStateException(const std::vector<std::string>& states);
	virtual ~InitialStateException() noexcept = default;
};

struct InvalidInputException : std::runtime_error
{
	InvalidInputException(const std::string& state, const std::string& input);
	virtual ~InvalidInputException() noexcept = default;
};

struct ParserException : std::runtime_error
{
	ParserException(const std::string& file);
	virtual ~ParserException() noexcept = default;
};

struct ReachableException : std::runtime_error
{
	ReachableException(const std::vector<std::string>& states);
	virtual ~ReachableException() noexcept = default;
};

struct ResolvableException : std::runtime_error
{
	ResolvableException(const std::string& target, const std::string& state);
	virtual ~ResolvableException() noexcept = default;
};

struct UniqueException : std::runtime_error
{
	UniqueException(const std::string& state);
	virtual ~UniqueException() noexcept = default;
};

}
#endif // FSML_EXCEPTIONS_HPP
