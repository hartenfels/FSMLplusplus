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

/**Abstract syntax tree representation of a state.*/
struct AstState
{
	std::string initial;
	std::string id;
	std::vector<AstStep> steps;
};

/**Abstract syntax tree representation of a state machine.*/
struct AstMachine
{
	std::vector<AstState> states;
};

}
#endif // FSML_AST_HPP
