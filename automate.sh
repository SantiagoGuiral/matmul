#! /bin/bash

THREADS=8
RESULTS="time.dat"
MATMUL="matmul"

if [[ ! -e "$RESULTS" ]]
	then
	touch time.dat
	printf "tseq,tfine,tcoarse,sfine,scoarse,threads\n">>time.dat
fi


if [[ -e "$MATMUL" ]]
then
	echo "Multithreading matrix multiplication"
	for i in {1..400}
	do
		echo "Iteration $i with $THREADS threads"
		./matmul -T $THREADS
		sleep 2
	done
else
	echo "Error - matmul file not found - execute in console: make"
fi
