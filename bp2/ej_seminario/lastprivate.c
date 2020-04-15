/*
    Nombre: Alejandro Molina Criado
    Fecha: 01 / 04 / 2020

    para compilar: gcc -O2 -fopenmp -o nombre nombre.c

    La clausula lastprivate combina la funcionalidad de private con la copia
    del último valor de las variables de la lista al salir del bloque paralelo

*/


#include <stdio.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num()
#endif

int main(){

    int i , n = 7 ,
        a[n] ,
        v;

    for(i = 0 ; i < n ; ++i) a[i] = i+1;
    
    #pragma omp parallel for lastprivate(v)
    for(i=0;i<n;++i){
        v = a[i];
        printf("thread %d v=%d \n" , omp_get_thread_num(),v);
    }

    printf("\nFuera de la sección parallel for\n*v = %d\n",v);

    return 0;
}
