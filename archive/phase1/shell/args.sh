#!/bin/bash

function display_args(){
	echo $1, $2; # Accessing arg1, and arg2
	echo "$@"; # printing all arguments as list at once
	echo "$*"; # Similar to $@, but arguments taken as single entity
	return 0;  # Return value
}


