/*
    Nombre: Alejandro Molina Criado
    Fecha: 25 / 03 / 2020

    para compilar: gcc -O2 -fopenmp -o nombre nombre.c
*/

// máximo N =2^32-1=4294967295 (sizeof(unsignedint) = 4 B)
#include <stdlib.h>	
#include <stdio.h>	
#include <omp.h> 
int main(int argc, char** argv){
  int i, j, k, l;
  double *v1, *v2, *v3;


  if (argc<2){
    printf("Faltan nº componentes del vector\n");
    exit(-1);
  }


  unsigned int N = atoi(argv[1]);

  v1 = (double*) malloc(N*sizeof(double));
  v2 = (double*) malloc(N*sizeof(double));
  v3 = (double*) malloc(N*sizeof(double));


  if ((v1 == NULL) || (v2 == NULL) || (v2 == NULL)) {
    printf("No hay suficiente espacio para los vectores \n");
    exit(-2);
  }


  double tiempo_inicial, tiempo_final, tiempo_total;
  #pragma omp parallel
  {
    #pragma omp sections
    {
      #pragma omp section
      for(i=0; i<N/4; i++){
        v1[i] = N*0.1+i*0.1;
        v2[i] = N*0.1-i*0.1;
      }

      #pragma omp section
      for(j=N/4; j<N/2; j++){
        v1[j] = N*0.1+j*0.1;
        v2[j] = N*0.1-j*0.1;
      }

      #pragma omp section
      for(k=N/2; k<3*N/4; k++){
        v1[k] = N*0.1+k*0.1;
        v2[k] = N*0.1-k*0.1;
      }

      #pragma omp section
      for(l=3*N/4; l<N; l++){
        v1[l] = N*0.1+l*0.1;
        v2[l] = N*0.1-l*0.1;
      }
    }

    #pragma omp single
      tiempo_inicial = omp_get_wtime();

    #pragma omp sections
    {
      #pragma omp section
      for(i=0; i<N/4; i++)
        v3[i] = v1[i] + v2[i];

      #pragma omp section
      for(j=N/4; j<N/2; j++)
        v3[j] = v1[j] + v2[j];

      #pragma omp section
      for(k=N/2; k<3*N/4; k++)
        v3[k] = v1[k] + v2[k];

      #pragma omp section
      for(l=3*N/4; l<N; l++)
        v3[l] = v1[l] + v2[l];
    }

    #pragma omp single
      tiempo_final = omp_get_wtime();
  }

  tiempo_total = tiempo_final - tiempo_inicial;


  if (N<10) {
  printf("Tiempo:%11.9f\t / Tamaño Vectores:%u\n",tiempo_total,N);
  for(i=0; i<N; i++)
    printf("/ V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n",
           i,i,i,v1[i],v2[i],v3[i]);
  }
  else
    printf("%11.9f\n", tiempo_total);  


  free(v1); 
  free(v2); 
  free(v3); 


  return 0;
}
