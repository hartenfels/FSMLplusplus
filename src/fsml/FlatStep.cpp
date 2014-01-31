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

bool operator<(const FlatStep& lhs, const FlatStep& rhs)
{
	return lhs.source < rhs.source || lhs.input < rhs.input || lhs.action < rhs.action ||
			lhs.target < rhs.target;
}

}
