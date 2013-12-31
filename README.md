FSML++
======
FSML implementation using C++.

Please see to-dos in issues and leave feedback there.

Build
-----
This program requires a compiler that supports the C++11 standard.

It also depends on Boost, which is provided in the lib folder to be linked statically. There's no need to build Boost, as only header files are used.

There is a Makefile for gcc provided, which will place compiled binaries into a folder called bin/. Enter ``make debug`` or ``make release`` to build a debug or fully-optimized executable. Use ``make simulation`` to build the sample interactive simulation. If you have Google's gtest unit testing library and pthread installed, use ``make test`` to build the unit test. ``make`` by itself will build everything.

Bash Script
-----------
There is a bash script called ``buildnrun.sh`` provided. It will make the release build, generate C++, LaTeX and Dot code, and finally run pdflatex and graphviz to yield two different PDF files.

Run FSML++
----------
The syntax for running the program is ``fsmlpp SOURCE``, where SOURCE is the path to a file containing FSML code.

Note that currently the program will look for the template files in the present working directory, so run it from the project's root directory.

The program will attempt to load the given file, parse the code inside, validate it and then generate a header file with an appropriate name. If any of the steps fail, an appropriate error is thrown.

Run Test
--------
The test requires Google's gtest library and pthread, which it depends on, to be installed. It will be attempted to link it via ``-lgtest -lpthread``. Execute the compiled ``fsmlpptest`` from the project's root directory so it can find all files.

Run Simulation
--------------
To run the simulation, just execute the compiled ``fsmlsim`` and enjoy the interactive simulation experience.
