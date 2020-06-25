// Programa principal 1. Lectores y escritores
// Garcia Gonzalez Aaron Antonio
// Sistemas Operativos 2CM9

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lectores_escritores.h"
#include "utilidades.h"

int rc=0; // Contador de lectores en ejecucion
unsigned int num_escritores, num_lectores;
sem_t mutex, db; // Semaforo mutex y semaforo base de datos

int main(int argc, char *argv[]){

	int estado,i,x,y;
	x=y=0;

	if ( argc < 3 ) { // Donde parametro 1 es el numero de escritores y parametro 2 es el numero de lectores
        printf("Numero de parametros incorrecto. Indicar el numero de datos a producir.\n") ;
        exit(1);              
    }
	
	num_escritores = atoi(argv[1]);
	num_lectores = atoi(argv[2]);
	int cola [num_lectores+num_escritores]; // arreglo de tamaño lectores + escritores 
	generaAleatorios(num_escritores,(num_escritores+num_lectores),cola); // las posiciones de los escritores esta distribuida en el arreglo, para identificar lectores y escritores, los lectores tienen valor cero y los lectores el valor de su posicion dentro del arreglo

	int eid[num_escritores], lid[num_lectores]; // Declaracion de los identicadores de los escritores y lectores
	pthread_t escritora[num_escritores],lectora[num_lectores]; // Declaracion de los hilos para escritores y lectores respectivamente

	sem_init(&mutex,0,1); // Inicalizamos en 1 el mutex, que sera utilizado para el control de la region critica, que es el numero de lectores en ejecucion
	sem_init(&db,0,1); // Inicalizamos en 1 el mutex db, que sera utilizado para el control de acceso a la base de datos

	for(i=0;i<num_lectores;i++){
		lid[i]=i;
		if((estado=pthread_create(&lectora[i],NULL,lector,(void *) &lid[i]))) // Creamos los hilos para los lectores, mandamos la funcion lector
			exit(estado);
	}

	for(i=0;i<num_escritores;i++){
		eid[i]=i;
		if((estado=pthread_create(&escritora[i],NULL,escritor,(void *) &eid[i]))) // Creamos los hilos para los escritores, mandamos la funcion escritor
			exit(estado);
	}

	// A continuacion realizamos la sincronizacion de los hilos, que hara que el hilo principal espere a los lectores y escritores, de acuerdo a una cola que asigna a los escritores de manera aleatoria simulando una verdadera cola, es como se ejecutara la funcion para esperar.
	for(i=0;i<20;i++){
		if(cola[i] == 1){ // escritores
			pthread_join(escritora[x],NULL);
			x++;
		}else{ // lectores
			pthread_join(lectora[y],NULL);
			y++;
		}
	}

	sem_destroy(&mutex);
	sem_destroy(&db);

	return 0;
}
