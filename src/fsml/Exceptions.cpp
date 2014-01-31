#include "fsml/Exceptions.hpp"
#include <sstream>
#include <boost/format.hpp>
#include <boost/spirit/include/karma.hpp>
namespace fsml
{ using namespace std; using boost::format; namespace karma = boost::spirit::karma;

// Format strings for exceptions
static constexpr char DETERMINISTIC[]{"Constraint violation - input \"%1%\" in state "
		"\"%2%\" is not deterministic."};
static constexpr char FILE_READ[]{"Error reading file \"%1%\"."};
static constexpr char FILE_WRITE[]{"Error writing file \"%1%\"."};
static constexpr char INITIAL_STATE_MISSING[]
		{"Constraint violation - missing an initial state."};
static constexpr char INITIAL_STATES[]
		{"Constraint violation - more than one initial state: %1%."};
static constexpr char INVALID_INPUT[]
		{"State \"%1%\" cannot handle the input \"%2%.\"."};
static constexpr char PARSER[]{"Error parsing file \"%1%\"."};
static constexpr char REACHABLE[]
		{"Constraint violation - state(s) not reachable: %1%."};
static constexpr char RESOLVABLE[]{"Constraint violation - target \"%1%\" in state "
		"\"%2%\" is not resolvable."};
static constexpr char UNIQUE[]{"Constraint violation - state \"%1%\" is not unique."};

/**Convenience function to create a comma-separated string from a multiset of string.
@param v The multiset of string of size >= 1.
@return A string containing each string from the multiset, separated with commas.
@throw out_of_range if the given multiset has size 0.*/
template <typename Iterator>
static string
stringListFrom(Iterator begin, const Iterator end)
{
	stringstream ss;
	ss << '"' << *begin << '"';
	for_each(next(begin), end, [&](const string& s){ss << ", \"" << s << '"';});
	return ss.str();
}

DeterministicException::DeterministicException(const string& i, const string& s) :
	runtime_error((format(DETERMINISTIC) % i % s).str()) {}

FileReadException::FileReadException(const string& f) :
	runtime_error((format(FILE_READ) % f).str()) {}

FileWriteException::FileWriteException(const string& f) :
	runtime_error((format(FILE_WRITE) % f).str()) {}

InitialStateException::InitialStateException(const multiset<string>& s) :
	runtime_error(s.empty() ? INITIAL_STATE_MISSING : (format(INITIAL_STATES) %
			stringListFrom(s.begin(), s.cend())).str()) {}

InvalidInputException::InvalidInputException(const string& s, const string& i) :
	runtime_error((format(INVALID_INPUT) % s % i).str()) {}

ParserException::ParserException(const string& f) :
	runtime_error((format(PARSER) % f).str()) {}

ReachableException::ReachableException(const vector<string>& s) :
	runtime_error((format(REACHABLE) % stringListFrom(s.begin(), s.cend())).str()) {}

ResolvableException::ResolvableException(const string& t, const string& s) :
	runtime_error((format(RESOLVABLE) % t % s).str()) {}

UniqueException::UniqueException(const string& s) :
	runtime_error((format(UNIQUE) % s).str()) {}

}
