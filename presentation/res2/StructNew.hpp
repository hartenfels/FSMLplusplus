#ifndef FSML_STRUCTNEW_HPP
#define FSML_STRUCTNEW_HPP
#include "fsml/Machine.hpp"
namespace fsml
{
/// @file Generated by FSML++.

/**This generated code will create a final state machine as per the following FSML code:

initial state FsmlCode {
  parse -> AstMachine;
}
state AstMachine {
  generateFsml -> FsmlCode;
  flatten -> FlatMachine;
}
state FlatMachine {
  revert -> AstMachine;
  construct/validate -> Machine;
  generateCode -> HPP;
}
state Machine {
  revert -> FlatMachine;
}
state HPP {
  construct/validate -> Machine;
}

@return An fsml::Machine corresponding to the FSML code it was generated from.*/
Machine createStructNew()
{
    return Machine{
		// Initial States
		std::vector<std::string>{
		"FsmlCode",
		},
		// Other States
		std::vector<std::string>{
		"AstMachine",
		"FlatMachine",
		"Machine",
		"HPP",
		},
		// Transitions
		std::vector<FlatStep>{
		{"FsmlCode", "parse", "", "AstMachine"},
		{"AstMachine", "generateFsml", "", "FsmlCode"},
		{"AstMachine", "flatten", "", "FlatMachine"},
		{"FlatMachine", "revert", "", "AstMachine"},
		{"FlatMachine", "construct", "validate", "Machine"},
		{"FlatMachine", "generateCode", "", "HPP"},
		{"Machine", "revert", "", "FlatMachine"},
		{"HPP", "construct", "validate", "Machine"},
		}
	};
}

}
#endif // FSML_STRUCTNEW_HPP
