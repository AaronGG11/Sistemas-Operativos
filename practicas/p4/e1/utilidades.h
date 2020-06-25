// Utilidades.h
// Libreria generica que contiene las funciones necesarias para generar aleatoriamente los indices de cola en que se ejecutaran los hilos ecritores y lectores respectivamente
// Garcia Gonzalez Aaron Antonio
// Sistemas Operativos 2CM9

// Funcion booleana o predicado que recibe dos argumentos, un entero x y un apuntador a entero (que apunta a un arreglo), la cual retorna 1 si el elemento esta en el arreglo y cero si no lo esta
int estaEn(int x, int *a){
    int contador = 0;
    for(int i=0; i<sizeof(a)/sizeof(a[0]); i++){
        if(x == a[i])
            contador += 1;
    }
    if(contador == 0)
        return 0;
    else
        return 1;
}

// Funcion que recibe el numero de lectores, el numero max (que es la suma de lectores y escritores, y un apuntador a entero que apunta a un arreglo que simulara una cola), no retorna nada, solo modifica los valores de cola, que contendra en las posciones aletorias la poscion de los escritores, y donde no coincide se quedara en cero que representa a los lectores
void generaAleatorios(int escritores, int max, int *cola){
    int i,j; // Contadores de ciclo for
    int aleatorio; // Numero auxiliar para almacenar temporalmente numeros aleatorios
    int temporal[escritores]; // Arreglo de tamaño escritores
    srand(time(NULL));
    aleatorio = 0;

    for(i=0;i<max;i++){ // Incializamos la cola y temporal en cero posicio na posicion
        cola[i]=0;
        if(i<escritores)
            temporal[i]=0;
    }

    for(i=0;i<escritores;i++){ // En el arreglo temporal, lo vamos a llenar de acuerdo a las posciones de 1 a max-1, sin repeticiones
        aleatorio=rand()%(1+max);
        while(estaEn(aleatorio,temporal)){
            aleatorio=rand()%(max);
        }
        if(!estaEn(aleatorio,temporal))
            temporal[i]=aleatorio;
    }

    for(i=0;i<max;i++){ // recorremos el arreglo cola 
        for(j=0;j<escritores;j++){ // recorremos el arreglo temporal
            if(i==temporal[j]) // cuando la posicion i sea igual a el contenido de temporal en la posicion j, entonces cola en la posicion i, sera igual a i o temporal en la posicion j
                cola[i]=temporal[j];
        }
    }
}