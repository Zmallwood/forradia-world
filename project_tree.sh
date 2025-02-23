#!/usr/bin/sh

eval $(dircolors -b)

viddy "TREE_COLORS='di=1;32:*.cpp=1;34:*.hpp=1;36' tree -C -F --dirsfirst ./develop | less +F"

