#include "fsml/State.hpp"
#include "fsml/Exceptions.hpp"
namespace fsml
{ using namespace std;

State::State(const string& i, const bool& init) : initial(init), id{i} {}

bool
State::addStep(const string& input, const Step& step)
{
	return steps.insert({input, step}).second;
}

State*
State::step(const string& input)
{
	const auto it = steps.find(input);
	if (it == steps.end())
		throw InvalidInputException(getId(), input);
	return it->second.invoke();
}

const bool&
State::isInitial() const
{
	return initial;
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
