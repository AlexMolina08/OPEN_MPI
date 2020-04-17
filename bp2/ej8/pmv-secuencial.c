/*
    Nombre: Alejandro Molina Criado
    Fecha: 01 / 04 / 2020

    para compilar: gcc -O2 -fopenmp -o pmv-secuencial pmv-secuencial.c
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//#define MATRIX_GLOBAL
#define MATRIX_DYNAMIC

#ifdef MATRIX_GLOBAL
#define MAX 20000
   
double m[MAX][MAX], v1[MAX], vf[MAX];
#endif
int main(int argc, char** argv)
{
	if (argc<2) 
	{	
		printf("ERROR: Introduce nº columnas\n");
		exit(-1);
	}

	int N = atoi(argv[1]);
	
	#ifdef MATRIX_GLOBAL
	    if (N>MAX) N=MAX;
	#endif
	#ifdef MATRIX_DYNAMIC
	    double *v1, *vf;
	    double **m;
	
	v1 = (double*) malloc(N * sizeof(double));
	vf = (double*) malloc(N * sizeof(double));
	m = (double**) malloc(N * sizeof(double*));
	
	for (int i=0; i<N; i++)
		m[i] = (double*)malloc(N * sizeof(double));
	
	if ((v1 == NULL) || (vf == NULL) || (m == NULL)) 
	{	
		printf("No hay suficiente espacio para reservar memoria \n");
		exit(-2);
	}
	#endif
 
	struct timespec cgt1,cgt2; 
	double ncgt;
	
	printf("Tamaño Matriz:%u x %u (%lu B)\n", N, N, sizeof(unsigned int));


	for (int i=0; i<N; ++i){ 
		v1[i] = N*0.1+i*0.1;
		for (int j=0; j<N; ++j)
			m[i][j] = N*0.1+i*0.1;
	} 
 
	//Multiplicacion
	clock_gettime(CLOCK_REALTIME,&cgt1);
	
	for (int i=0; i<N; ++i) 
		for (int j=0; j<N; ++j)
			vf[i] += m[i][j] * v1[j];
 
	clock_gettime(CLOCK_REALTIME,&cgt2);
	
	//Salida del resultado y el tiempo de ejecucion
	ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+
       (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

	if (N<12) 
	{
		printf("Tiempo:%11.9f\t / Tamaño columnas:%u\n",ncgt,N); 
		for (int i=0; i<N; ++i)
		{
			printf("/ ");
			for (int j=0; j<N-1; ++j)
				printf("(%8f*%8f)+", m[i][j], v1[j]);
			printf("(%8f*%8f) =", m[i][N-1], v1[N-1]);
			printf(" V2[%d] = %8f /\n", i, vf[i]);
		}
	}
	else
		printf("Tiempo:%11.9f\t / Tamaño columnas:%u\t/ V2[0] = %8.6f / / V2[%d] = %8.6f /\n", ncgt, N, vf[0], N-1, vf[N-1]);

	#ifdef MATRIX_DYNAMIC
		for(int i = 0; i < N; ++i)
			free(m[i]);
		free(m);
		free(v1);
		free(vf);
	#endif

	return 0;
}