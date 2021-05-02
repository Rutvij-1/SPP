#!/bin/bash
if [ "$1" = "1" ]
then
	filenames=(0.txt 5.txt 10.txt 15.txt 20.txt 30.txt 40.txt 50.txt 55.txt 60.txt 70.txt 75.txt 80.txt 85.txt 90.txt)
else
	filenames=(t6 t19 t29 t31 t43 t49 t75 t77 t78 t91)
fi
for name in "${filenames[@]}"
do
	echo $name
	perf stat ./$2 < Q$1/$name > Q$1out/$name
done
