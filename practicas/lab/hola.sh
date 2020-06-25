#!/bin/bash
# Autor: Aaron Garcia
# Fecha: 21/08/2019
# Descripcion: 
# Entrada_
# Salida: 



num=10


echo "Hola Aaron"
echo Mi ruta es: 
pwd
echo "Hoy es: ` date "+%y-%m-%d" `"
echo "La hora es: ` date "+%H-%M-%S" `"
echo "El valor de num es: " $num
echo "¿Cual es tu nombre: "
read nombre
echo "Tu eres:" $nombre
let op=num+5
echo "Resultado:" $op











# usuario grupo otros
# read -> 4
# write -> 2
# excecute -> 1
# No permission -> 0 
# chmod 775 
# man chmod -> manual de linux
