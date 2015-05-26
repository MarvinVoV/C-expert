#!/bin/bash

for var in {a..z}
do
	echo $var;
done


for((i=0; i<10; i++)){
	echo $i | tr '\n' ' '
}

echo hello
i=10;
while [ $i -gt 0 ]
do
	let i--;
	echo $i;
done
