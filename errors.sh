#!/bin/sh
make release
bin/fsmlpp tests/determinismNotOk.fsml
bin/fsmlpp tests/idsNotOk.fsml
bin/fsmlpp tests/initialNotOk.fsml
bin/fsmlpp tests/parserError.fsml
bin/fsmlpp tests/reachabilityNotOk.fsml
bin/fsmlpp tests/resolutionNotOk.fsml
