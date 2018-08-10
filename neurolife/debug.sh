#!/bin/bash
target="./bin/ubuntu" 
cd $target
gdb --args ./nlifed ./../default.cfg

