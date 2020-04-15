/*
    Nombre: Alejandro Molina Criado
    Fecha: 25/03/2020

    para compilar: gcc -O2 -fopenmp -o nombre nombre.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


void funcionA(){
    printf("En funcA: esta seccion ejecuta el thread %d\n",omp_get_thread_num());
}

void funcionB(){
    printf("En funcB: esta seccion ejecuta el thread %d\n",omp_get_thread_num());
}


int main(int argc , char **argv){

    #pragma omp parallel sections
    {
            #pragma omp section
                (void) funcionA();
            #pragma omp section
                (void) funcionB();

    }

}