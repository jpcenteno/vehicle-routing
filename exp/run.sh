#! /bin/bash

# Lee las instancias de la carpeta instances de forma ordenada y las ejecuta para un algoritmo en particular

declare -a files

i=1
for vrp in `ls instances/ | sort -n`
do
	files[i++]="${vrp}"
done

for (( i = 1; i <= ${#files[@]}; i++ )); do
	./vrp -a 2-opt -e < "instances/${files[i]}"
done 