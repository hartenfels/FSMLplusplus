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

}
