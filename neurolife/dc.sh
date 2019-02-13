#!/bin/bash
target="./bin/ubuntu" 
cd $target
gdb --args ./nlifec ./../world.cfg 192.168.1.41
