#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "Sistema.h"
#include "Elem.h"
#include "Pila.h"

int main(int argc, char const *argv[]){
    Pila pila;
    char caracter;
    int shmid;
    key_t llave;
    int opc,contador;

    llave=ftok("/bin/pwd",34);
    if(llave == -1){
        perror("\nError en ftok");
        exit(-1);
    }
    
    shmid = shmget(llave,sizeof(struct Nodo)*10, IPC_CREAT|0777);
    if(shmid == -1){
        perror("\nError en shmget");
        exit(-1);
    }

    pila = (Pila)shmat(shmid,0,0);
    contador = 0;

    while(1){
        printf("\nIntroduce una opcion: \n");
        printf("t1. Ingresar elemento\n");
        printf("t2. Retirar\n");
        printf("t3. Visualizar\n");
        printf("t4. Finalizar\n");
        printf("    Selecciona una opcion: ");
        scanf("%d",&opc);

        switch(opc){
            case 1:
                if(contador>10){
                    printf("Pila llena, no se inserto elemento\n");
                    break;
                }
                else{
                    printf("[PUSH]. Introduce el valor: ");
                    PausaPrograma();
                    scanf("%c",&caracter);
                    pila = Push(caracter,pila);
                    contador++;
                    break;
                }
            case 2:
                printf("[POP]. Retirar ultimo elemento: ");
                ImpElem(Top(pila));
                pila = Pop(pila);
                break;
            case 3:
                printf("[SHOW]. Visualizar\n");
                impPila(pila);
                break;
            case 4:
                printf("\nFinalizar\n");
                shmdt(pila);
                shmctl(shmid,IPC_RMID,0); 
                exit(1);
                break;
            default: 
                printf("Opcion no valida\n");
                break;
        }
    }
    return 0;
}
