#!/usr/bin/sh

set -e

eval $(dircolors -b)

FULL_TREE="$(TREE_COLORS='di=1;32:*.cpp=1;34:*.hpp=1;36' tree -C -F -I 'build|CMakeFiles' --dirsfirst ./develop)"
CLICKED_ROW=$(echo "$FULL_TREE" | tac | fzf --ansi --bind 'ctrl-w:page-up,ctrl-s:page-down')
ROW_IDX=$(tree -I 'build|CMakeFiles' --dirsfirst ./develop | grep -n "$(echo "$CLICKED_ROW")" | cut -d: -f1)
FILE_PATH="$(tree -fi -I 'build|CMakeFiles' --dirsfirst ./develop | sed -n "${ROW_IDX}p")"
tmux send-keys -t 1 "nvim $FILE_PATH" C-m

./project_tree.sh

