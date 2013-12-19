#ifndef FSML_GENERATOR_HPP
#define FSML_GENERATOR_HPP
#include "fsml/Machine.hpp"
#include "parser/FlatMachine.hpp"
#include <boost/spirit/include/karma.hpp>
namespace fsml
{

// TODO: Move to a sensible place.
std::string fileToString(const std::string& file);
const std::string generateHeader(const std::string& identifier,
	const std::string& fsmlCode);
const std::string generateSource(const std::string& identifier,
	const FlatMachine& fm);
const std::string generateLatex(const std::string& init,
	const std::vector<std::string>& states,	const std::vector<StepTup>& self,
	const std::vector<StepTup>& other);

template <typename OutputIterator>
const bool generateKarma(OutputIterator sink, const std::string& identifier,
		const std::vector<std::string>& states)
{
	using boost::spirit::karma::generate;
	return generate(sink, *("\t" << +boost::spirit::ascii::alpha << ",\n"), states);
}

}
#endif // FSML_GENERATOR_HPP
