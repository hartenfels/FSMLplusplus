#include "fsml/State.hpp"
#include "validator/Exception.hpp"
namespace fsml
{ using namespace std;

State::State(const string& i) : id{i} {}

const bool
State::addStep(const string& input, const Step& step)
{
	return steps.insert(pair<string, Step>(input, step)).second;
}

State* const
State::step(const string& input)
{
	return steps.at(input).invoke();
}

const string&
State::getId() const
{
	return id;
}

const unordered_map<string, Step>&
State::getSteps() const
{
	return steps;
}

}
