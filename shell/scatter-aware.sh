#!/bin/bash

if [ `id -u` -ne 0 ]; 
then
	echo "Permission denied."
	exit 1
fi

if ! type "expect" > /dev/null;
then
	apt-get install expect
fi

flag="y"
i=0
while [ $flag != "n" ]
do
	read -p "Enter ip:" hosts[$i]
	read -p "Enter ${hosts[$i]}'s user:" users[$i]
	read -p "Enter ${hosts[$i]}'s passwd:" passwds[$i]
	let i++
	read -p "Continue(y/n)" flag
done

echo $flag ${#hosts[@]}


