#!/bin/bash
pushd .
cd pascalsrc
fpc flossy.pas
popd
mv pascalsrc/flossy .

