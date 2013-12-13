FSML++
======
FSML implementation using C++.

To Do
-----
- [ ] Generate a better, more fitting abstract syntax so that we don't need so much code to transform it again.
- [ ] Fix code generation to be less magic (needs better abstract syntax).
- [ ] Find a good way to generate visual representation with proper layout.
- [ ] Proper run options.
- [ ] Documentation.

Build
-----
This program requires a compiler that supports the C++11 standard.
It also depends on Boost, which is provided in the lib folder to be linked statically.
There is a Makefile for gcc provided. Enter ``make debug`` or ``make release`` to build the appropriate targets. ``make`` by itself will build both.

Run
---
The syntax for running the program is ``fsmlpp SOURCE``, where SOURCE is the path to a file containing FSML code.
Note that currently the program will look for the template files in the present working directory, so run it from the appropriate location (i.e. not the bin folder).
The program will attempt to load the given file, parse the code inside, validate it and then generate a Machine[timestamp].hpp and a Machine[timestamp].cpp file, throwing something when a step fails.
