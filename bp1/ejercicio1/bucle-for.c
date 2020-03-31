/*
    Nombre: Alejandro Molina Criado
    Fecha: 25 / 03 / 2020

    para compilar: gcc -O2 -fopenmp -o nombre nombre.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc , char **argv){

    int i,n=9;

    if (argc < 2){
        fprintf(stderr,"\n[ERROR] - FALTA Nº ITERACIONES");
        exit(-1);
    }

    n = atoi(argv[1]);

    #pragma omp parallel for
    
        for(i=0;i<n;i++){
            printf("thread %d ejecuta la iteración %d del bucle\n",omp_get_thread_num(),i);
        }
    

    return 0;

}