#include "generate/Generatesamplefsml.hpp"
namespace fsml
{

Machine
createsamplefsml()
{
    return Machine{
		// Initial States
		{{
		"locked",
		}},
		// Other States
		{{
		"unlocked",
		"exception",
		}},
		// Steps
		{{
		FlatStep("locked", "ticket", "collect", "unlocked"),
		FlatStep("locked", "pass", "alarm", "exception"),
		FlatStep("unlocked", "ticket", "eject", "unlocked"),
		FlatStep("unlocked", "pass", "", "locked"),
		FlatStep("exception", "ticket", "eject", "exception"),
		FlatStep("exception", "pass", "", "exception"),
		FlatStep("exception", "mute", "", "exception"),
		FlatStep("exception", "release", "", "locked"),
		}}};
}

}
