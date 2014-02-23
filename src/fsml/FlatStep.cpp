#include "fsml/FlatStep.hpp"
#include <boost/format.hpp>
namespace fsml
{ using namespace std; using boost::format;

FlatStep::FlatStep(const string& s, const string& i, const string& a, const string& t) :
	source{s}, input{i}, action{a}, target{t} {}

FlatStep::operator string() const
{
	return (format("{\"%1%\", \"%2%\", \"%3%\", \"%4%\"}") % source % input % action %
			target).str();
}

const string
FlatStep::getStepText() const
{
	return action.empty() ? input : input + '/' + action;
}

bool
operator==(const FlatStep& lhs, const FlatStep& rhs)
{
	return lhs.source == rhs.source && lhs.action == rhs.action &&
			lhs.input == rhs.input && lhs.target == rhs.target;
}

bool
operator!=(const FlatStep& lhs, const FlatStep& rhs)
{
	return !operator==(lhs, rhs);
}

bool operator<(const FlatStep& lhs, const FlatStep& rhs)
{
	// Lexographical comparison
	if (lhs.source < rhs.source) return true;
	if (rhs.source < lhs.source) return false;
	if (lhs.input < rhs.input) return true;
	if (rhs.input < lhs.input) return false;
	if (lhs.action < rhs.action) return true;
	if (rhs.action < lhs.action) return false;
	if (lhs.target < rhs.target) return true;
	return false;
}

}
