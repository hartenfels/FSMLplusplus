FSML++
======
FSML implementation using C++. See https://github.com/slebok/slepro/tree/master/languages/fsml for the reference implementation in Prolog.

Requirements
------------
This program requires a compiler that supports the C++11 standard.

It also depends on Boost, which is provided in the lib folder to be linked statically. There's no need to build Boost since the project exclusively uses header-only libraries.

For unit testing, Google's gtest library and pthread are required.

Finally, since the program generates LaTeX and Dot code, you will need appropriate programs for compiling them into an image format, like pdfTeX and Graphviz.

Build
-----
There is a Makefile for gcc provided, which will place compiled binaries into a folder called bin.

Use ``make debug`` or ``make release`` to build a debug or fully-optimized executable. The binaries will be called ``fsmlpp_debug`` and ``fsmlpp`` respectively.

Use ``make simulation`` to build the sample interactive simulation. If you have Google's gtest unit testing library and pthread installed. The resulting binary will be called ``fsmlpp_simulation``.

Use ``make test`` to build the test, the required libraries will be attempted to be linked via ``-lgtest -lpthread`` The resulting binary will be called ``fsmlpp_test``.

Use ``make table`` to build an executable that prints a table from the goedelization function for use in our presentation. The resulting binary will be called ``fsmlpp_table``.

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
The syntax for running the test is ``fsmlpp_test TEST...``, where TEST is one or more of the following:

- **constraint** execute the simple constraints tests given.
- **model \<ni\> \<ns\> \<t\> \<maxT\>** execute identity testing of the parser, abstract syntax and flat representation. This will generate flat representations with **ni** initial states, **ns** non-initial states and transition configurations from **t** to **maxT**. These will be converted to an abstract syntax tree, which is converted to FSML code. This code is parsed into another abstract syntax tree and another flat representation is constructed from it. The abstract syntax trees and flat representation are compared to each other and should always be equal.
- **machine \<ns\> \<t\> \<maxT\>** execute oracle testing of the machine against Boost's directed graph and, if the machine is actually valid, perform identity testing against the flat representation. This will generate flat representations together with an equivalent Boost.Graph directed graph with one initial state, **ns** non-initial states and transition configurations from **t** to **maxT**. A breadth-first search is performed on the graph. If all states are reachable, the flat representation is converted to a machine, which is converted back into another flat representation and the two are checked for equality. If not all states are reachable, it is verified that the construction of the machine fails with the same states reachable.
- **sanityEqual \<ni\> \<ns\> \<t\>** execute a simple equality sanity check. This will generate a flat representation and abstract syntax with **ni** initial states, **ns** non-initial states and a transition configuration **t** and compare them against themselves.
- **sanityInequal \<ni1\> \<ns1\> \<t1\> \<ni2\> \<ns2\> \<t2\>** execute an inequality sanity check. This will generate two flat representations and abstract syntax trees with **ni1** and **ni2** initial states, **ns1** and **ns2** non-initial states and transition configurations **t1** and **t2** respectively. They are then compared against each other expecting them to be inequal. Note that the test will fail if two identical configurations are given.

Note that the **ni** and **ns** are limited by the size of ``size_t`` on your platform, while **t** and **maxT** are of arbitrary size.

Run Simulation
--------------
To run the simulation, just execute the compiled ``fsmlpp_simulation`` and enjoy the interactive simulation experience.
