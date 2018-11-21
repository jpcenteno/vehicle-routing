#! /bin/bash

# Genera instancias de vrp
for (( i = 10; i <= 300; i++ )); do
	echo $i | ./gen > EXP/"instance_$i"
done 