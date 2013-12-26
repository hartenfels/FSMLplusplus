#include "samplefsml.hpp"
namespace fsml
{ using std::vector; using std::string;

Machine
createsamplefsml()
{
    return Machine{
		// Initial States
		vector<string>{
		"locked",
		},
		// Other States
		vector<string>{
		"unlocked",
		"exception",
		},
		// Transitions
		vector<FlatStep>{
		FlatStep("locked", "ticket", "collect", "unlocked"),
		FlatStep("locked", "pass", "alarm", "exception"),
		FlatStep("unlocked", "ticket", "eject", "unlocked"),
		FlatStep("unlocked", "pass", "", "locked"),
		FlatStep("exception", "ticket", "eject", "exception"),
		FlatStep("exception", "pass", "", "exception"),
		FlatStep("exception", "mute", "", "exception"),
		FlatStep("exception", "release", "", "locked"),
		}
	};
}

}
