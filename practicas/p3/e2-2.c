#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Sistema.h"

void *messageOne(void *id);
void *messageTwo(void *id);

int main(int argc, char const *argv[]){
    int error;
    int *valor;
    int id[2] = {1,2};
    pthread_t hilos[2];

    for(int i = 0; i<2; i++){
        if(i==0){ // Se trata del primer hijo
            error = pthread_create(&hilos[i],NULL,messageOne,&id[i]);
        }else{ // Se trata del segundo hilo
            error = pthread_create(&hilos[i],NULL,messageTwo,&id[i]);
        }
        if(error){ // Error al crear hilo
            printf("Error al crear hilo: %d\n", i+1);
            exit(-1);
        }
    }
    exit(0);
    sleep(1);
    for(int i = 0; i<2; i++){
       pthread_join(hilos[i], (void **)&valor);
    }
    limpiaBuffer();
    printf("\nFIN\n");

    return 0;
}


void *messageOne(void *id){
    char pal[] = "aaron";
    printf("\n[%d]\t", *(int*)id);
    for(int i=0; i<strlen(pal); i++){
        printf("%c\t", pal[i]);
    }

    pthread_exit(id);
}

void *messageTwo(void *id){
    char pal[] = "miguel";
    printf("\n[%d]\t", *(int*)id);
    for(int i=0; i<strlen(pal); i++){
        printf("%c\t", pal[i]);
    }

    pthread_exit(id);
}