#!/bin/bash
target="./bin/ubuntu" 
cd $target
gdb --args ./serverd ./../world.cfg server
