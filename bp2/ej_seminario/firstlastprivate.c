/*
    Nombre: Alejandro Molina Criado
    Fecha: 01 / 04 / 2020

    para compilar: gcc -O2 -fopenmp -o nombre nombre.c

    En este codigo , la variable suma se incializa a 0 en todos los threads y al salir 
    se tiene el valor de la instancia suma del ultimo thread ejecutado

*/

/*
SALIDA:

thread 3 suma a[6] suma=6
thread 1 suma a[2] suma=2
thread 1 suma a[3] suma=5
thread 0 suma a[0] suma=0
thread 0 suma a[1] suma=1
thread 2 suma a[4] suma=4
thread 2 suma a[5] suma=9

fuera de la seccion parallel suma=6
*/


#include <stdio.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num()
#endif

int main(){

    int i , n = 7,
        a[n] , 
        suma = 0;
    
    for(i=0;i<n;i++) a[i] = i;

    #pragma omp parallel for firstprivate(suma) lastprivate(suma)
    for(i=0;i<n;++i){
        suma = suma + a[i];
        printf("thread %d suma a[%d] suma=%d\n",omp_get_thread_num(),i,suma);
    }

    printf("\nfuera de la seccion parallel suma=%d\n",suma);

    return 0;
}
