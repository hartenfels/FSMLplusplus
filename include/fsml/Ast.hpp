#ifndef FSML_AST_HPP
#define FSML_AST_HPP
#include <string>
#include <vector>
namespace fsml
{

/**Abstract syntax tree representation of a transition.*/
struct AstStep
{
	std::string input;
	std::string action;
	std::string target;
};

bool operator==(const AstStep& lhs, const AstStep& rhs);
bool operator!=(const AstStep& lhs, const AstStep& rhs);

/**Abstract syntax tree representation of a state.*/
struct AstState
{
	std::string initial;
	std::string id;
	std::vector<AstStep> steps;
};

bool operator==(const AstState& lhs, const AstState& rhs);
bool operator!=(const AstState& lhs, const AstState& rhs);

/**Abstract syntax tree representation of a state machine.*/
struct AstMachine
{
	std::vector<AstState> states;
};

bool operator==(const AstMachine& lhs, const AstMachine& rhs);
bool operator!=(const AstMachine& lhs, const AstMachine& rhs);

}
#endif // FSML_AST_HPP
