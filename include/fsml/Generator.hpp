#ifndef FSML_GENERATOR_HPP
#define FSML_GENERATOR_HPP
#include "fsml/FlatMachine.hpp"
#include "fsml/Machine.hpp"
#include <boost/spirit/include/karma.hpp>
namespace fsml
{

// TODO: Move to a sensible place.
std::string fileToString(const std::string& file);
const std::string generateCode(const std::string& identifier,
	const std::string& fsmlCode, const FlatMachine& flatMachine);
const std::string generateLatex(const std::string& init,
	const std::vector<std::string>& states,	const std::vector<StepTup>& self,
	const std::vector<StepTup>& other);

}
#endif // FSML_GENERATOR_HPP
