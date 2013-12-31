#!/bin/sh
make release
bin/Release/fsmlpp Sample.Fsml
pdflatex SampleFsml
dot -Tpdf SampleFsml.dot 1>SampleFsml.dot.pdf
