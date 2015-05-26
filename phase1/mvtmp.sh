#!/bin/bash

for f in $(ls .)
do
    if [ $f -eq "phase1" ]; then
        continue
    fi
    mv $f ./phase1
done
