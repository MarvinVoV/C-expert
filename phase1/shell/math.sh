#!/bin/bash

# Math calculations
n1=3;
n2=4;
let result=n1+n2;
echo $result

let result++
echo $result

let result+=n1;
echo $result

# The [] operator can be used similar to the let command as follows
result=$[ n1 + n2 ]  # the space between [ and variable is option.
echo $result

result=$[ n1++];
echo $result

# (()) can alse be used. $ prefixed with a variable name is used when the (()) operator is used.

result=$(( n1 + n2 )); # no space between = and $
echo $result

# expr can alse be used for basic operations
result=`expr 3 + 4`
echo $result

result=$(expr $n1 + 5);
echo $result;

# can be used for float
echo "4 * 0.56" | bc
