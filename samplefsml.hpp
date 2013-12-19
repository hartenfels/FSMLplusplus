#ifndef FSML_GENERATEsamplefsml_HPP
#define FSML_GENERATEsamplefsml_HPP
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
Machine createsamplefsml();

}
#endif // FSML_GENERATEsamplefsml_HPP
