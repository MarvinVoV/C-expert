#!/bin/bash

array_var=(1 2 3 4);
array_var[0]="test1"
array_var[1]="test2"
array_var[2]="test3"
varay_var[3]="test4"

echo ${array_var[0]}
#echo $array_var[0]   # test1[0], the usage is error.
echo ${array_var[$index]}
echo ${array_var[*]}

echo ${array_var[@]}

echo ${#array_var[@]}
