#include "generate/Generate.hpp"
namespace fsml
{

Machine
createMachine1386353591()
{
    return Machine(
		// States
		{{
			"locked",
			"unlocked",
			"exception",
		}},
		// Initial State
		"locked",
		// Steps
		{{
			StepTup("locked", "ticket" , "collect", "unlocked"),
			StepTup("locked", "pass", "alarm", "exception"),
			StepTup("unlocked", "ticket", "eject", "unlocked"),
			StepTup("unlocked", "pass", "", "locked"),
			StepTup("exception", "ticket", "eject", "exception"),
			StepTup("exception", "pass", "", "exception"),
			StepTup("exception", "mute", "", "exception"),
			StepTup("exception", "release", "", "locked"),
		}});
}

}
