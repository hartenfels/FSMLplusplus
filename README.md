FSML++
======
FSML implementation using C++.

Please see to-dos in issues and leave feedback there.

Build
-----
This program requires a compiler that supports the C++11 standard.

It also depends on Boost, which is provided in the lib folder to be linked statically.

There is a Makefile for gcc provided, which will place compiled binaries into a folder called bin/. Enter ``make debug`` or ``make release`` to build a debug or fully-optimized executable. Use ``make simulation`` to build the sample interactive simulation. ``make`` by itself will build everything.

Run FSML++
----------
The syntax for running the program is ``fsmlpp SOURCE``, where SOURCE is the path to a file containing FSML code.

Note that currently the program will look for the template files in the present working directory, so run it from the appropriate location (i.e. not the bin folder).

The program will attempt to load the given file, parse the code inside, validate it and then generate a Machine[timestamp].hpp and a Machine[timestamp].cpp file, throwing something when a step fails.

Run Simulation
--------------
To run the simulation, just execute the compiled ``fsmlsim`` and enjoy the interactive simulation experience.
