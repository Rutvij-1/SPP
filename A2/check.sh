#!/bin/bash
temp=${3:${#3}-1}
if [ "$temp" = "/" ]; then
out_folder=${3:0:${#3}-1}
else
out_folder=$3
fi
temp=${2:${#2}-1}
if [ "$temp" = "/" ]; then
in_folder=$2
else
in_folder="$2/"
fi
if [[ ! -d $out_folder ]]
then
mkdir $out_folder
fi
for inname in $in_folder*
do
	echo $inname
	name=${inname:${#2}}
	./$1 < $inname > $out_folder/$name
	cat $out_folder/$name | grep 'Time taken'
done
