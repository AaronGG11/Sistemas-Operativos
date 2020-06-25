#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <string.h>

#define CANCELAR 1 // Mayor prioridad
#define RESERVAR 2
#define CONSULTAR 3
#define FINALIZAR 4 // Menor prioridad

struct mensaje{
    long tipo;
    char accion[10]; // Se refiere a cualquier peticion 
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

    // Enviar mensajes
    control = 0; 
    while(control != FINALIZAR){
        printf("1. Cancelar\n2. Reservar\n3. Consultar\n4. Finalizar\n   Seleccione una opcion: ");
        scanf("%d",&control);
        switch(control){
            case CANCELAR:
                strcpy(msg.accion,"CANCELAR");
                msg.tipo=CANCELAR;
                msgsnd(msgid,&msg,tam,0); // Esperara hasta que se pueda enviar el mensaje
                break;
            case RESERVAR:
                strcpy(msg.accion,"RESERVAR");
                msg.tipo=RESERVAR;
                msgsnd(msgid,&msg,tam,0); // Esperara hasta que se pueda enviar el mensaje
                break;
            case CONSULTAR:
                strcpy(msg.accion,"CONSULTAR");
                msg.tipo=CONSULTAR;
                msgsnd(msgid,&msg,tam,0); // Esperara hasta que se pueda enviar el mensaje
                break;
            case FINALIZAR: 
                strcpy(msg.accion,"FINALIZAR");
                msg.tipo=FINALIZAR;
                msgsnd(msgid,&msg,tam,0); // Esperara hasta que se pueda enviar el mensaje
                break;
            default:
                printf("ERROR, opcion no valida\n");
                printf("Finalizando ...\n");
                exit(1);
                break;
        }
    }
    printf("Finalizando ...\n");

    return 0;
}
