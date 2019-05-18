#!/bin/sh
#
# Utilisation: ./run.sh DIRNAME ARGS
# Arguments:
# - DIRNAME est le nom du sous-répertoire de `codes` à compiler; on suppose que
#   ce répertoire contient un Makefile qui construit un exécutable nommé `a.out`

docker build --no-cache -t inf2610-code-runner-image -f \
    .docker/Dockerfile-run . 2>&1 > /dev/null
docker run -e "DIR=$1" inf2610-code-runner-image "${@:2}"