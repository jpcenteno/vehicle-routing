#! /bin/bash

# Genera instancias de vrp en la carpeta instances
for (( i = 10; i <= 300; i++ )); do
	echo $i | ./gen > instances/"$i"
done 
