#ifndef FSML_VALIDATOR_HPP
#define FSML_VALIDATOR_HPP
#include "fsml/Machine.hpp"
#include "parser/Machine.hpp"
namespace fsml { namespace validator
{

// TODO: move to Machine's constructor once a proper abstract syntax is built.
Machine validate(const ast::Machine& astMachine);

}}
#endif // FSML_VALIDATOR_HPP
