#include "SampleFsml.hpp"
#include <iostream>
#include <string>

int
main()
{
	using namespace fsml; using namespace std;
	// Construct FSM
	Machine m{createSampleFsml()};
	// Register some functions
	m.registerAt("alarm",   [](){cout << "action: alarm\n";});
	m.registerAt("collect", [](){cout << "action: collect\n";});
	m.registerAt("eject",   [](){cout << "action: eject\n";});
	// Simulate
	cout << "Starting simulation of sample.fsml.\n" <<
			"Enter input at prompt, enter invalid input to end.\n";
	string s;
	while (true) {
		cout << "State: " << m.getCurrentState().getId() << ". Input? ";
		cin >> s;
		m << s;
	}
}

