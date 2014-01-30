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
	Action() = default;
	Action(const std::string& id);
	virtual ~Action() = default;

	/**@return The Action's name*/
	virtual const std::string& getId() const;
    /**Registers the given function.
    @param f The function.*/
	virtual void registerFunction(const ActionFunction& f);
	/**Invokes the previously registered function.*/
	virtual void invoke() const;
protected:
	/// The name of this action.
	const std::string id;
    /// The function.
    ActionFunction func;
};

}
#endif // FSML_ACTION_HPP
