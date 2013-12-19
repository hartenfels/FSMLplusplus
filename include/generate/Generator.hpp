#ifndef FSML_GENERATOR_HPP
#define FSML_GENERATOR_HPP
#include "fsml/Machine.hpp"
#include "parser/Machine.hpp"
namespace fsml
{

// TODO: Move to a sensible place.
std::string fileToString(const std::string& file);
const std::string generateHeader(const std::string& identifier,
	const std::string& fsmlCode);
const std::string generateSource(const std::string& identifier,
	const ast::Machine& am);
const std::string generateLatex(const std::string&, const ast::Machine& am);

}
#endif // FSML_GENERATOR_HPP
