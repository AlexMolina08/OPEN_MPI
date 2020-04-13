/*
    Nombre: Alejandro Molina Criado
    Fecha: 01 / 04 / 2020

    para compilar: gcc -O2 -fopenmp -o nombre nombre.c

    La cláusula private establece que cada subproceso tiene su propia instancia de una variable
    o conjunto de ellas
*/
/*
SALIDA:
thread 4 suma a[6]
thread 3 suma a[5]
thread 1 suma a[2]
thread 1 suma a[3]
thread 0 suma a[0]
thread 2 suma a[4]
thread 0 suma a[1]

* thread 2 suma=4
* thread 4 suma=6
* thread 1 suma=5
* thread 3 suma=5
* thread 0 suma=1
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

    #pragma omp parallel private(suma)
    {
        suma = 0;
        #pragma omp for
        for(i = 0 ; i < n ; ++i){
            suma = suma + a[i];
            printf("thread %d suma a[%d]\n",omp_get_thread_num() , i);
        }

    }

            printf("\n* thread %d suma=%d",omp_get_thread_num(),suma);

    printf("\n");

    return 0;
}