/*
    Nombre: Alejandro Molina Criado
    Fecha: 01 / 04 / 2020

    para compilar: gcc -O2 -fopenmp -o privateModificado privateModificado.c
*/

#include <stdio.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num()
#endif

int main(){
    int i , n = 7,
        a[n],
        suma;
    
    for(i = 0 ; i < n ; ++i) a[i] = i; 

    #pragma omp parallel
    {
        suma = 0;
        #pragma omp for
        for(i = 0 ; i < n ; ++i){
            suma = suma + a[i];
            printf("(thread %d suma = %d)\n" , omp_get_thread_num() , suma);
            printf("thread %d suma a[%d]\n",omp_get_thread_num() , i);
        }

        printf("\n* thread %d suma=%d",omp_get_thread_num(),suma);

    }

    printf("\n");

    return 0;
}