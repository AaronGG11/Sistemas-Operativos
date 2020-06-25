#!/bin/bash
# Autor: Aaron Garcia
# Fecha: 21/08/2019
# Descripcion: 
# Entrada_
# Salida: 


function suma
{
    local a=`expr $1 + $2`
    echo "La suma de $1 y $2 es $a"
}



echo "Los argumentos son: $@" # #@ == $*
echo "El numero de argumentos es: $#" 
suma $1 $2

if [ $1 -gt $2 ]
then
    echo "$1 es mas grande que $2"
else
    echo "$2 es mas grande que $1"
fi