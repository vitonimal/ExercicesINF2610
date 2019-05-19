#!/bin/bash
#
# Utilisation: ./run.sh DIRNAME ARGS
# Arguments:
# - DIRNAME est le nom du sous-répertoire de `codes` à compiler; on suppose que
#   ce répertoire contient un Makefile qui construit un exécutable nommé `a.out`

docker build --no-cache -t inf2610-code-runner-image -f \
    .docker/Dockerfile-run . 2>&1 > /dev/null
argv="$@"
argv[0]="./a.out"
docker run -e "DIR=$1" -e "ARGC=$#" -e "ARGV=$argv" inf2610-code-runner-image
