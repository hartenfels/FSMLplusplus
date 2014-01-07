#ifndef FSML_INPUTOUTPUT_HPP
#define FSML_INPUTOUTPUT_HPP
#include "Machine.hpp"
namespace fsml
{
/**@file Contains file input and output related functions.*/

/**Attemps to read the given file into a string.
@param file The file path.
@return A string containing the content of the read file.
@throw FileReadException if file could not be read.*/
std::string readFile(const std::string& file);

/**Attempts to write the given content to the given file.
@param file The file path.
@param content The text to write to the file.
@throw FileWriteException if file could not be written to.*/
void writeFile(const std::string& file, const std::string& content);

/**Attemps to read, parse and construct a Machine from the given file.
@param fsmlFile The file path.
@return Constructed Machine.
@see readFile for file-related exceptions.
@see parse for parser-related exceptions.
@see Machine for validation-related exceptions.*/
Machine machineFromFile(const std::string& fsmlFile);

}
#endif // FSML_INPUTOUTPUT_HPP
