#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <string.h>

#define CANCELAR 1
#define RESERVAR 2
#define CONSULTAR 3
#define FINALIZAR 4


struct mensaje{
    long tipo;
    char accion[9];
};

int main(int argc, char const *argv[]){
    key_t llave;
    int msgid, tam, control;
    struct mensaje msg;

    llave = ftok("/bin/ls", 10);
    if(llave == -1){
        perror("Error en ftok\n");
        exit(-1);
    }
    msgid = msgget(llave,IPC_CREAT|0777);
    if(msgid == -1){
        perror("Error en msgget\n");
        exit(-1);
    }

    tam = sizeof(msg) - sizeof(msg.tipo);
    control = 0;

    printf("Peticiones acumuladas: \n");

    while(1){
    // Recibir mensajes
        if(msgrcv(msgid,&msg,tam,CANCELAR,IPC_NOWAIT) == -1){ 
            if(msgrcv(msgid,&msg,tam,RESERVAR,IPC_NOWAIT) == -1){
                if(msgrcv(msgid,&msg,tam,CONSULTAR,IPC_NOWAIT) == -1){
                    if(msgrcv(msgid,&msg,tam,FINALIZAR,IPC_NOWAIT) == -1){
                        printf("\tFINALIZAR ...\n");
                        break; // Salimos del bucle, a lo mas puede haber un FINALIZAR en toda la ejecucion
                    }
                }
                else{
                    printf("\tCONSULTAR ...\n");
                }
            }else{
                printf("\tRESERVAR ...\n");
            }
        }else{
            printf("\tCANCELAR ...\n");
        }
        control = msg.tipo;
    }
    msgctl(msgid,IPC_RMID,0); // Liberamos la cola de mensajes 

    return 0;
}
