#ifndef FSML_VALIDATOR_EXCEPTION_H
#define FSML_VALIDATOR_EXCEPTION_H
#include <string>
namespace fsml { namespace validator
{

constexpr char NO_INITIAL[] = "FSM is missing an initial state.";
constexpr char INITIALS[] = "Both %1% and %2% are initial states.";
constexpr char DISTINCT[] = "%1% is not a distinct state ID.";
constexpr char DETERMINISTIC[] = "%1% in %2% is not deterministic.";
constexpr char RESOLVABLE[] = "%1% in %2% is not resolvable.";
constexpr char REACHABLE[] = "State(s) not reachable: %1%";

class Exception
{
public:
	Exception(const std::string&);
protected:
};

}}
#endif // FSML_VALIDATOR_EXCEPTION_H
