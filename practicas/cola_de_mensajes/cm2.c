#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <string.h>

struct mensaje{
    long tipo;
    char cadena[50];
};

int main(int argc, char const *argv[]){
    key_t llave;
    int msgid, tam;
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
    do{
        // Recibir mensaje 
        printf("Recibiendo mensaje ...\n");
        msgrcv(msgid,&msg,tam,1,0);
        printf("Mensaje recibido:\n\tTIPO\t> %ld\nMENSAJE\t> %s\n", msg.tipo, msg.cadena);

        // Enviar mensaje 
        printf("Teclee cadena: ");
        fgets(msg.cadena,sizeof(msg.cadena),stdin);
        msg.tipo=2;
        msgsnd(msgid,&msg,tam,0);
    }while(strcmp(msg.cadena,"FIN") == 0);


    // Liberar 
    printf("Finalizando ...\n");
    msgctl(msgid,IPC_RMID,0);

    return 0;
}
