#ifndef FSML_SAMPLEFSML_HPP
#define FSML_SAMPLEFSML_HPP
#include "fsml/Machine.hpp"
namespace fsml
{

/**This generated code will create a final state machine as per the following FSML code:

initial state locked {
  ticket/collect -> unlocked;
  pass/alarm -> exception;
}
state unlocked {
  ticket/eject;
  pass -> locked;
}
state exception {
  ticket/eject;
  pass;
  mute;
  release -> locked;
}

@return An fsml::Machine corresponding to the FSML code it was generated from.*/
Machine createSampleFsml()
{
    return Machine{
		// Initial States
		{
			"locked",
		},
		// Other States
		{
			"unlocked",
			"exception",
		},
		// Transitions
		{
			{"locked", "ticket", "collect", "unlocked"},
			{"locked", "pass", "alarm", "exception"},
			{"unlocked", "ticket", "eject", "unlocked"},
			{"unlocked", "pass", "", "locked"},
			{"exception", "ticket", "eject", "exception"},
			{"exception", "pass", "", "exception"},
			{"exception", "mute", "", "exception"},
			{"exception", "release", "", "locked"},
		}
	};
}

}
#endif // FSML_SAMPLEFSML_HPP
