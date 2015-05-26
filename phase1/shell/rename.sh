#!/bin/bash

count=1;
for f in *.txt
do
	newname=${f%%.*}-$count.${f##*.}
	mv "$f" "$newname" 2>/dev/null
	if [ $? -eq 0 ];
	then
		echo "Renaming $f to $newname"
		let count++;
	fi
done
