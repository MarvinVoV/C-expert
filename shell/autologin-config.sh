#!/bin/bash

if [ `id -u` -ne 0 ];then
	echo "Permission denied."
	exit 1
fi

if ! type "expect" > /dev/null; then
	apt-get install expect
fi
