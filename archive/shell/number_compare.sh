#!/bin/bash

echo "*** Numeric comparisions"

x=5
y=10

if (test $x -eq $y) then
    echo "$x = $y"
else
    echo "$x != $y"
fi
