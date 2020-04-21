#!/bin/bash

submodules=(
    seastar
    scylla-jmx
    scylla-tools
)

for submodule in "${submodules[@]}"; do
    GIT_DIR="$submodule/.git" git pull origin master
    SUMMARY=$(git submodule summary $submodule)
    git commit -m "Update $submodule submodule" -m "$SUMMARY" $submodule
done
