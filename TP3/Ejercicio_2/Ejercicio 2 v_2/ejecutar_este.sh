#!/bin/bash

# Trabajo Práctico nro 3
# Ejercicio 2
# Integrantes del grupo:
# Greve Iván - 38617763
# Boullon Daniel Ernesto - 36385582
# Silvero Heber Ezequiel - 36404597
# Valenzuela Juan Santiago - 38624490
# Nicolás Satragno - 38527273

echo '~~~~~~~~~~~~~'
echo ' Ejercicio 2 '
echo '~~~~~~~~~~~~~'
echo "1) Caso Archivos" 
echo "2) Caso FIFO"
echo "3) Caso Memoria Compartida" 
echo "4) Caso Socket(1PC)"
echo "5) Salir"

read -r opt

case $opt in
    1)
		./ARCHIVO/Servidor & ( sleep 1 & ./ARCHIVO/Cliente )
        ;;
    2)
		./FIFO/Servidor & ( sleep 1 & ./FIFO/Cliente )
        ;;
    3)
    	echo "Memoria:"
		./MEMORIA/Servidor & ( sleep 1 & ./MEMORIA/Cliente ) 
        ;;
    4)
     	./SOCKET\ 1/Servidor & ( sleep 1 & ./SOCKET\ 1/Cliente )
     	;;
    5)
        break
        ;;
    *) echo "Incorrecto :(";;
esac

sleep 3

echo "FIN"
