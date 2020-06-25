#include <stdio.h>		//biblioteca estandar
#include <stdlib.h>      //biblioteca para los permisos 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define TMENSAJE 256

int main(int argc, char const *argv[]){
    int er, re;
    int salir, cambio;
    int fifo_er, fifo_re;
    char mensaje[TMENSAJE];
    er = mkfifo("fiforadio_er", S_IRWXU);
    re = mkfifo("fiforadio_re", S_IRWXU);
    fifo_er = open("fiforadio_er", O_WRONLY);  //descriptor de archivo de la primer pila
    fifo_re = open("fiforadio_re", O_RDONLY);  //descriptor de archivo de la segunda pila
    do{
        printf("EMISOR <._.>\n");
        fgets(mensaje,TMENSAJE,stdin);
        write(fifo_er,mensaje,strlen(mensaje)+1);
        salir=strcmp(mensaje,"CAMBIO Y FUERA\n");
        cambio=strcmp(mensaje,"CAMBIO\n");
        if(cambio == 0){ // Va a empezar a leer
            do{
                read(fifo_re,mensaje,TMENSAJE);
                printf("\nRECEPTOR <*_*> %s", mensaje);
                salir=strcmp(mensaje,"CAMBIO Y FUERA\n");
                cambio=strcmp(mensaje,"CAMBIO\n");
            }while(cambio != 0 || salir != 0);
        }
    }while(salir != 0);
    close(fifo_er);
    close(fifo_re);

    return 0;
}
