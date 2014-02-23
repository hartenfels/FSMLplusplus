#ifndef FSML_GENERATETEST_HPP
#define FSML_GENERATETEST_HPP
#include "fsml/FlatMachine.hpp"
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/number.hpp>
namespace fsml
{

FlatMachine geno(const size_t& numInitials, const size_t& numStates,
		const boost::multiprecision::cpp_int& transitions);

void genoTest();

}
#endif // FSML_GENERATETEST_HPP
