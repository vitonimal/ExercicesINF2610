#!/bin/sh

docker build --no-cache -t inf2610-code-runner-base-image -f \
    .docker/Dockerfile-base .