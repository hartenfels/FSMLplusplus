#ifndef FSML_FSMLPPFSML_HPP
#define FSML_FSMLPPFSML_HPP
#include "fsml/Machine.hpp"
namespace fsml
{
/// @file Generated by FSML++.

/**This generated code will create a final state machine as per the following FSML code:

initial state FsmlCode {
	parse -> AstMachine;
}

state AstMachine {
	flatten -> FlatMachine;
}

state FlatMachine {
	construct/validate -> Machine;
	generateCode -> HPP;
	generateLatex -> TEX;
	generateDot -> DOT;
}

state Machine {
}

state HPP {
}

state TEX {
}

state DOT {
}

@return An fsml::Machine corresponding to the FSML code it was generated from.*/
Machine createFsmlppFsml()
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
		"TEX",
		"DOT",
		},
		// Transitions
		std::vector<FlatStep>{
		{"FsmlCode", "parse", "", "AstMachine"},
		{"AstMachine", "flatten", "", "FlatMachine"},
		{"FlatMachine", "construct", "validate", "Machine"},
		{"FlatMachine", "generateCode", "", "HPP"},
		{"FlatMachine", "generateLatex", "", "TEX"},
		{"FlatMachine", "generateDot", "", "DOT"},
		}
	};
}

}
#endif // FSML_FSMLPPFSML_HPP
