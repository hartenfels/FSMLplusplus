#ifndef FSML_INPUTOUTPUT_HPP
#define FSML_INPUTOUTPUT_HPP
#include "Machine.hpp"
namespace fsml
{
/**@file Contains file input and output related functions.*/

/**Attemps to read the given file into a string.
@param file The file path.
@return A string containing the content of the read file.
@throws FileReadException if file could not be read.*/
std::string readFile(const std::string& file);
/**Attemps to read, parse and construct a Machine from the given file.
@param fsmlFile The file path.
@return Constructed Machine.
@see readFile for file-related exceptions.
@see parse for parser-related exceptions.
@see Machine for validation-related exceptions.*/
Machine machineFromFile(const std::string& fsmlFile);

}
#endif // FSML_INPUTOUTPUT_HPP
