#include "validator/Exception.hpp"
#include <iostream>
namespace fsml { namespace validator
{

Exception::Exception(const std::string& s)
{
	std::cerr << "Constraint violation: " << s << '\n';
}

}}
