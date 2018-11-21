#! /bin/bash

# Lee las instancias de una carpeta y las ejecuta

declare -a files

i=1
for vrp in EXP/*
do
	files[i++]="${vrp}"
done

for (( i = 1; i <= ${#files[@]}; i++ )); do
	#echo "${files[i]}"
	./vrp -a goloso < "${files[i]}"
done 