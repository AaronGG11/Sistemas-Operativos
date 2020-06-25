#! /bin/bash
# Aaron Antonio Garcia Gonzalez

num_lineas=$(cat $1 | wc -l)
contador=0 
auxiliar=0  
posicion=0
num=$2

for i in $( cut -d' ' -f1 albumes.txt )
    do
    arreglo[$contador]=$i
    let contador+=1
done

if [ $num -gt $num_lineas ]; then
    echo "Numero solicitado es mayor al total de bandas" $2 ">" $num_lineas
else
    for j in `seq 1 $num`;do
    let auxiliar=${arreglo[0]}
    let posicion=0

    for i in `seq 0 $num_lineas`;do
        if [ ${arreglo[$i]} -ge $auxiliar ]; then
            let auxiliar=${arreglo[$i]}
            let posicion=$i+1
        fi
    done
    sed -n ${posicion}p "albumes.txt"
    let arreglo[$posicion-1]=0
done
fi

