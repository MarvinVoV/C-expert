#!/bin/bash

echo $SHELL
filename="sample.jpg";
name=${filename%.*}
echo File name is $name.  # the output is sample

extension=${filename#*.};
echo extension is $extension # the output is jpg

var=hack.fun.book.txt
echo ${var%%.*} # output is hack. because %% is greedy
echo ${var##*.}  # output is txt. because ## is greedy
