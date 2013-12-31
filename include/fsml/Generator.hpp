#ifndef FSML_GENERATOR_HPP
#define FSML_GENERATOR_HPP
#include "fsml/FlatMachine.hpp"
#include "fsml/Machine.hpp"
namespace fsml
{

const std::string generateCode(const std::string& name, const std::string& fsmlCode,
	const FlatMachine& flatMachine);

const std::string generateLatex(const FlatMachine& flatMachine);

const std::string generateDot(const std::string& name, const FlatMachine& flatMachine);

}
#endif // FSML_GENERATOR_HPP
