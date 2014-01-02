FSML++
======
FSML implementation using C++.

Requirements
------------
This program requires a compiler that supports the C++11 standard.

It also depends on Boost, which is provided in the lib folder to be linked statically. There's no need to build Boost, as only header files are used.

For unit testing, Google's gtest library and pthread are required.

Finally, since the program generates LaTeX and Dot code, you will need appropriate programs for compiling them, e.g. pdfTeX and Graphviz

Build
-----
There is a Makefile for gcc provided, which will place compiled binaries into a folder called bin.

Use ``make debug`` or ``make release`` to build a debug or fully-optimized executable. The binaries will be called ``fsmlpp_debug`` and ``fsmlpp`` respectively.

Use ``make simulation`` to build the sample interactive simulation. If you have Google's gtest unit testing library and pthread installed. The resulting binary will be called ``fsmlpp_simulation``.

Use ``make test`` to build the unit test, the required libraries will be attempted to be linked via ``-lgtest -lpthread`` The resulting binary will be called ``fsmlpp_test``.

``make`` by itself will build all targets.

Bash Script
-----------
There is a bash script called ``buildnrun.sh`` provided. It will make the release build, generate C++, LaTeX and Dot code for the Sample.Fsml, and finally run ``pdflatex`` and ``graphviz`` to yield two different PDF files.

Run FSML++
----------
The syntax for running the program is ``fsmlpp SOURCE``, where SOURCE is the path to a file containing FSML code.

Note that the program will look for the template files in the present working directory, so run it from the project's root directory.

The program will attempt to load the given file, parse the code inside, validate it and then generate a C++ header file, LaTeX file and Dot file with an appropriate name. If any of the steps fail, an appropriate error is thrown.

Run Test
--------
Execute the compiled ``fsmlpp_test`` from the project's root directory so it can find all files. No special output means that the expected errors or lack thereof occurred. Otherwise, there will be a message about each failed test.

Run Simulation
--------------
To run the simulation, just execute the compiled ``fsmlpp_simulation`` and enjoy the interactive simulation experience.
