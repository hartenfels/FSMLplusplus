FSML++
======
FSML implementation using C++.

Please see to-dos in issues and leave feedback there.

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
