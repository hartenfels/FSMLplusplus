#ifndef FSML_INPUTOUTPUT_HPP
#define FSML_INPUTOUTPUT_HPP
#include "Machine.hpp"
namespace fsml
{

std::string readFile(const std::string& file);
Machine machineFromFile(const std::string& fsmlFile);

}
#endif // FSML_INPUTOUTPUT_HPP
