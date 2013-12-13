#ifndef FSML_GENERATE1386937547_HPP
#define FSML_GENERATE1386937547_HPP
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
Machine createMachine1386937547();

}
#endif // FSML_GENERATE1386937547_HPP
