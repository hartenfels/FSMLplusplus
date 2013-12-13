#ifndef FSML_ACTION_HPP
#define FSML_ACTION_HPP
#include <functional>
#include <string>
namespace fsml
{

typedef std::function<void ()> ActionFunction;

class Action
{
public:
	virtual ~Action() = default;
	virtual void registerFunction(const ActionFunction& f);
	virtual void invoke() const;
protected:
    ActionFunction func;
};

}
#endif // FSML_ACTION_HPP
