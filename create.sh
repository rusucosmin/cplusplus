#!/bin/bash

mkdir -p $1
cd $1
newString=${1,,}

cpp=$newString".cpp"
in=$newString".in"
out=$newString".out"

touch $cpp
touch $in
touch $out

vim $cpp -c "vs "$in -c "sp "$out -c ":30winc <"



