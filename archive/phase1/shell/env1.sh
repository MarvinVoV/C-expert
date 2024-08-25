#!/bin/bash

# Check for super user
if [ $UID -ne 0 ]; then
	echo "Non root user. please run as root."
else
	echo "Root user"
fi


