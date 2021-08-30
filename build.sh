#!/bin/bash

code="$PWD"
opts=-g
cd ./debug/ > /dev/null
msbuild $opts $code/msbuild -o ./debug/
cd $code > /dev/null
