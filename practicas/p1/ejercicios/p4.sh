#! /bin/bash
# Aaron Antonio Garcia Gonzalez
echo "número de parámetros = $#"
# si número de parámetros igual o menor con 1


function ordena {
    contador=0

    for i in "$@"
    do
        arreglo[$contador]=$i
        let contador=$contador+1
    done

    for ((i=0; i <= $((${#arreglo[@]} - 2)); ++i))
        do
            for ((j=((i + 1)); j <= ((${#arreglo[@]} - 1)); ++j))
            do
                if [[ ${arreglo[i]} -gt ${arreglo[j]} ]]
                then
                    # echo $i $j ${arr[i]} ${arr[j]}
                    tmp=${arreglo[i]}
                    arreglo[i]=${arreglo[j]}
                    arreglo[j]=$tmp         
                fi
            done
        done

    for var in "${arreglo[@]}"
    do
    echo "${var}"
    done
}

if [ $# -lt 2 ]
then
    echo "ERROR - Hay menos de DOS argumentos"
elif [ $# -gt 8 ]
then
    echo "ERROR - Hay mas de OCHO argumentos"
else  
    ordena $*
fi

