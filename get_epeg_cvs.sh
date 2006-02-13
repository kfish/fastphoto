#!/bin/sh

cvs -z3 -d:pserver:anonymous@cvs.sourceforge.net:/cvsroot/enlightenment co e17/libs/epeg
mv e17/libs/epeg . && rm -rf e17
cd epeg && ./autogen.sh && make
