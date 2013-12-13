#ifndef FSML_STATE_HPP
#define FSML_STATE_HPP
#include "fsml/Step.hpp"
#include <string>
#include <unordered_map>
namespace fsml
{

class State
{
public:
	virtual ~State() = default;
	virtual const bool addStep(const std::string& input, const Step& step);
	virtual State* const step(const std::string& input);
	virtual const std::unordered_map<std::string, Step>& getSteps() const;
protected:
	std::unordered_map<std::string, Step> steps;
};

}
#endif // FSML_STATE_HPP
