#ifndef FSML_GENERATOR_HPP
#define FSML_GENERATOR_HPP
#include "fsml/Ast.hpp"
#include "fsml/FlatMachine.hpp"
#include "fsml/Machine.hpp"
namespace fsml
{
/**@file Contains all code generation functions.*/

const std::string generateFsml(const AstMachine& astMachine);

/**Generates usable C++ code for a header file to construct a Machine from.
@param name File name.
@param fsmlCode Parsed fsml code.
@param flatMachine Flattened fsml machine.
@return A string containing the generated code.*/
const std::string generateCode(const std::string& name, const FlatMachine& flatMachine);

/**Generates Latex code for visual representation
@param flatMachine Flattened fsml machine.
@return A string containing the generated code.*/
const std::string generateLatex(const FlatMachine& flatMachine);

/**Generates Graphviz code for visual representation
@param name File name.
@param flatMachine Flattened fsml machine.
@return A string containing the generated code.*/
const std::string generateDot(const std::string& name, const FlatMachine& flatMachine);

}
#endif // FSML_GENERATOR_HPP
