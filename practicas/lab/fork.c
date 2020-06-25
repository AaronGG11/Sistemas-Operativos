#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h> 


int main(){
        int num;
        int pid;
        int pidh;

        pid = fork();
        if(pid==-1){// error en la llamada fork
                perror("\nError  en la llamada fork");
                exit(-1);
        } else if(pid == 0){ // intrucciones del proceso hijo
                printf("\n\nHijo > Estoy iniciando mi ejecucion");
                printf("\nHijo > El valor de num es %d",num);
                printf("\nHijo > El pid es %d", getpid());
                printf("\nHijo > El pid de mi padre es %d", getppid());
                //sleep(30);
                exit(0); // proceso terminado de manera exitosa
        } else { // instrucciones del proceso padre
                printf("\nPadre > Estoy iniciando mi ejecucion");
                printf("\nPadre > El valor de num es %d",num);
                sleep(30);
                printf("\nPadre > El pid es %d", getpid());
                printf("\nPadre > El pid de mi hijo es %d", pid);
                pidh = wait(NULL); // obtener variable de terminacion del hijo
                printf("\n\nPadre > Mi hijo %d terminosu ejercucion\n\n", pid);
        }

}                                                                                                      
