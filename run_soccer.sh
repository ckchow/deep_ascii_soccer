#!/bin/bash

# need to clean up crap before halting so the shell doesn't look crazy
trap ctrl_c INT

function ctrl_c() {
	reset
}

./qcompile.sh random west
./soccer
reset
