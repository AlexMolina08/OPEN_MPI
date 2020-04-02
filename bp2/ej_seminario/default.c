/*
    Nombre: Alejandro Molina Criado
    Fecha: 01 / 04 / 2020

    para compilar: gcc -O2 -fopenmp -o nombre nombre.c

    La clausula firstprivate combina la funcionalidad de private y además las variables de la lista
    se inicializan al entrar en la región paralela

*/
#include <stdio.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num()
#endif

int main(){

    return 0;
}