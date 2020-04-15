/*
    Nombre: Alejandro Molina Criado
    Fecha: 25 / 03 / 2020

    para compilar: gcc -O2 -fopenmp -o nombre nombre.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){

    int n = 9 ; 
    int i , a , b[n];

    for(i=0 ; i<n ; i++) b[i]=-1;

    #pragma omp parallel
    {

        #pragma omp single
        {
            printf("Escribe valor de inicialización a:");
            scanf("%d",&a);
            printf("Single ejecutada por el hilo %d\n",omp_get_thread_num());
        } // <-- Barrera
        #pragma omp for
        for(i=0;i<n;i++){
            b[i]=a;
        }


        #pragma omp master
        {
            printf("Dentro de la región parallel:\n");
            for(i=0;i<n;i++) printf("b[%d]=%d\t",i,b[i]);
            printf("Directiva master ejecutada por el hilo %d\n",omp_get_thread_num());
        }
    }
}