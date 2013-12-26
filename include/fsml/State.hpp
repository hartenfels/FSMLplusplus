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
	State(const std::string& id);
	virtual ~State() = default;
	virtual bool addStep(const std::string& input, const Step& step);
	virtual State* step(const std::string& input);
	virtual const std::string& getId() const;
	virtual const std::unordered_map<std::string, Step>& getSteps() const;
protected:
	const std::string id;
	std::unordered_map<std::string, Step> steps;
};

}
#endif // FSML_STATE_HPP
