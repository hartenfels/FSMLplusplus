#!/bin/sh
make release
bin/fsmlpp Sample.Fsml
pdflatex SampleFsml
dot -Tpdf SampleFsml.dot 1>SampleFsml.dot.pdf
