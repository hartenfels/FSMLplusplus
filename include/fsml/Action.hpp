#ifndef FSML_ACTION_HPP
#define FSML_ACTION_HPP
#include <functional>
#include <string>
namespace fsml
{

typedef std::function<void ()> ActionFunction;

/**Represents a transition action.*/
class Action
{
public:
	virtual ~Action() = default;

    /**Registers the given function.
    @param f The function. */
	virtual void registerFunction(const ActionFunction& f);
	/**Invokes the previously registered function.*/
	virtual void invoke() const;
protected:
    ///The function.
    ActionFunction func;
};

}
#endif // FSML_ACTION_HPP
