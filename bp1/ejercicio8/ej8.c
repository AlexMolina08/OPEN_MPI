/*
    Nombre: Alejandro Molina Criado
    Fecha: 25 / 03 / 2020

    para compilar: gcc -O2 -fopenmp -o nombre nombre.c
*/
#include<stdio.h>
#include<omp.h>
#include<time.h>
#include <stdlib.h>

int main(int nargs, char** argv)
{
int i;
double ncgt,cgt1;
unsigned int N = atoi(argv[1]);
double v1[N], v2[N], v3[N];
printf("Tamaño Vectores:%u (%lu B)\n",N, sizeof(unsigned int)); 

#pragma omp parallel sections private(i)
{
	#pragma omp section
	for (i=0 ; i<1/4*N; i++){
		v1[i] = N*0.1+i*0.1;
		v2[i] = N*0.1-i*0.1;
	}
	#pragma omp section
	for (i=1/4*N ; i<2/4*N; i++){
		v1[i] = N*0.1+i*0.1;
		v2[i] = N*0.1-i*0.1;
	}
	#pragma omp section
	for (i=2/4*N ; i<3/4*N; i++){
		v1[i] = N*0.1+i*0.1;
		v2[i] = N*0.1-i*0.1;
	}
	#pragma omp section
	for (i=3/4*N ; i<N; i++){
		v1[i] = N*0.1+i*0.1;
		v2[i] = N*0.1-i*0.1;
	}
}

cgt1=omp_get_wtime();
#pragma omp parallel sections private(i)
{
	#pragma omp section
	for (i=0 ; i<1/4*N; i++)
		v3[i] = v1[i] + v2[i];
		
	#pragma omp section
	for (i=1/4*N ; i<2/4*N; i++)
		v3[i] = v1[i] + v2[i];

	#pragma omp section
	for (i=2/4*N ; i<3/4*N; i++)
		v3[i] = v1[i] + v2[i];

	#pragma omp section
	for (i=3/4*N ; i<N; i++)
		v3[i] = v1[i] + v2[i];
}

ncgt=omp_get_wtime() - cgt1;

//Imprimir resultados
  if (N<12) {
  printf("Tiempo:%11.9f\t / Tamaño Vectores:%u\n",ncgt,N); 
  for(i=0; i<N; i++) 
    printf("/ V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n",
           i,i,i,v1[i],v2[i],v3[i]); 
  }
  else
    printf("Tiempo:%11.9f\t / Tamaño Vectores:%u\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) / / V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n"
	,ncgt,N,v1[0],v2[0],v3[0],N-1,N-1,N-1,v1[N-1],v2[N-1],v3[N-1]);


return 0;
}

