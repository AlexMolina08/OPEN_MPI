/*
    Nombre: Alejandro Molina Criado
    Fecha: 01 / 04 / 2020

    para compilar: gcc -O2 -fopenmp -o nombre nombre.c

    Con la cláusula atomic asegura la exclusión mutua en una región de memoria
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

//#define GLOBAL
#define DINAMIC

#ifdef GLOBAL
	#define MAX 33554432
#endif

int main(int argc, char const *argv[]){
	if(argc != 2){
        printf("Error de argumentos %s", argv[0]);
        return(EXIT_FAILURE);
    }
    
    struct timespec cgt1, cgt2;
    double ncgt;

    int N = atoi(argv[1]);

    #ifdef GLOBAL
    	if(N > MAX) N = MAX;
        int matriz[N][N];
        int vector[N];
        int vector_resultado[N];
        printf("Ejecutado GLOBALMENTE\n");
    #endif

    #ifdef DINAMIC
        int **matriz, *vector, *vector_resultado;
        matriz = (int**) malloc(N * sizeof(int*));
        for(int i = 0; i < N; ++i)
            matriz[i] = (int*) malloc(N * sizeof(int));
       
        vector = (int*) malloc(N * sizeof(int));
        vector_resultado = (int*) malloc(N * sizeof(int));
        printf("Ejecutado DINAMICAMENTE\n");
    #endif
    
    #pragma omp parallel for
    for(int i = 0; i < N; ++i){
    	vector[i] = i;
    	#pragma omp parallel for
        for(int j = 0; j < N; ++j)
        	matriz[i][j] = i + j;
	}

	clock_gettime(CLOCK_REALTIME, &cgt1);
	int suma;
	//Resultado
	for(int i = 0; i < N; i++){
		suma = 0;
		#pragma omp parallel for reduction(+:suma)
		for(int j = 0; j < N; j++)
			suma += vector[j] * matriz[i][j];
			
		vector_resultado[i] = suma;
	}
	
	clock_gettime(CLOCK_REALTIME, &cgt2);
	ncgt = (double) (cgt2.tv_sec - cgt1.tv_sec) + (double) (cgt2.tv_nsec - cgt1.tv_nsec) / (1.e+9);
	
	printf("Tiempo: %11.9f seg.\t / Tamaño vectores: %u\n", ncgt, N);
	if(N < 15)
		for(int i = 0; i < N; i++){
			printf("V_RESULTADO[%d] = %d  ", i, vector_resultado[i]);
			printf("\n");
		}
	else{
		printf("V_RESULTADO[0] = %d  ", vector_resultado[0]);
		printf("V_RESULTADO[%d] = %d  ", N - 1, vector_resultado[N - 1]); printf("\n");
	}
	
	#ifdef DINAMIC
	for(int i = 0; i < N; i++)
		free(matriz[i]);
	
	//LIBERAMOS ESPACIO
	free(matriz); free(vector); free(vector_resultado);
	#endif
	    
    return 0;
}