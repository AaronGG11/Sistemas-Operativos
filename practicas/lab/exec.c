#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h> 

// int execl(char * path, char  * arg0, ..., char * argn, (char*)0)
// int execv (char * path, char * arv[])

int main(int argc, char const *argv[]){
	int pid = fork();
	int resultado;
	char * arreglo[] = {"ad","5",NULL};

	if(pid == -1){ // error

	}else if(pid == 0){ // codigo hijo 
		//resultado = execl("/bin/mkdir","mkdir","pruebas",NULL); // Para que el hijo tenga su propio codigo 
		resultado = execv("ad",arreglo);
		printf("Fallo exec, codigo: %d\n", resultado);
		exit(resultado);
	}else{ // padre	
		wait(NULL);
	}

	return 0;
}