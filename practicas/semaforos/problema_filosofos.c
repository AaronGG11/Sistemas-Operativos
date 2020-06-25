
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

//para compilar usa el -lpthread

#define NFILOSOFOS 5
#define HAMBRIENTO 0
#define COMIENDO 1  
#define PENSANDO 2


sem_t sfilosofos[NFILOSOFOS];                           //un semaforo por filosofo inicializado en 0, para que espere si alguno de sus tenedores no esta disponible
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;        //mutex para controlar el acceso a región critica
int edo_filosofos[NFILOSOFOS];                          //para el control de los estados en que puede estar un filosofo

void pensar(void){
   sleep(5);
}

void comer (void){
    sleep(5);
}
int obtener_ifilosofo (int idF){
    if (idF == 0)
       return NFILOSOFOS-1; 
    else
        return idF - 1;
}
int obtener_dfilosofo (int idF){
    if (idF == (NFILOSOFOS-1))
        return 0;
    else
        return idF + 1;
}

void tenedores_disponibles(int idF){
    int ifilosofo, dfilosofo;
    ifilosofo = obtener_ifilosofo(idF);
    dfilosofo = obtener_dfilosofo(idF);
    if(edo_filosofos[idF]==HAMBRIENTO && edo_filosofos[ifilosofo] != COMIENDO && edo_filosofos[dfilosofo] != COMIENDO) {
        edo_filosofos[idF] = COMIENDO;
        printf("\nFILOSOFO %i \t> Estoy comiendo \n",idF);
        sem_post(&sfilosofos[idF]);
    }
}

void tomar_tenedores(int idF){
   pthread_mutex_lock(&mutex);              //down mutex
   edo_filosofos[idF]=HAMBRIENTO;           //El filosofo tiene hambre, intentará comer
   printf("\nFILOSOFO %i \t> Tendo hambre, intentare comer \n",idF);
   tenedores_disponibles(idF);              //El filosofo verificará si sus tenedores están disponibles para tomarlos e iniciar a comer
   pthread_mutex_unlock(&mutex);            //up mutex
   sem_wait(&sfilosofos[idF]);              //down sfilosofos[idF]
}

void colocar_tenedores(int idF){
    int ifilosofo,dfilosofo;
    ifilosofo = obtener_ifilosofo(idF);
    dfilosofo = obtener_dfilosofo(idF);
    pthread_mutex_lock(&mutex);
    edo_filosofos[idF]=PENSANDO;
    printf("\nFILOSOFO %i \t> Estoy pensando \n",idF);
    tenedores_disponibles(ifilosofo);
    tenedores_disponibles(dfilosofo);
    pthread_mutex_unlock(&mutex);
}

void * filosofo(void *idF){
   int idFilosofo=*(int *)idF;
   
    while(1){
        pensar();
        tomar_tenedores(idFilosofo);
        comer();
        colocar_tenedores(idFilosofo);
    }
}

int main(){
int id[NFILOSOFOS]={0,1,2,3,4};
int i;
pthread_t filosofos[NFILOSOFOS];

   for(i=0;i<NFILOSOFOS;i++){
       sem_init(&sfilosofos[i],0,0);
   }

   for(i=0;i<NFILOSOFOS;i++){
      pthread_create(&filosofos[i],NULL,filosofo,&id[i]); 
   }

   for(i=0;i<NFILOSOFOS;i++){
      pthread_join(filosofos[i],NULL); 
   }
}






 







