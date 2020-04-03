/*
    Nombre: Alejandro Molina Criado
    Fecha: 01 / 04 / 2020

    para compilar: gcc -O2 -fopenmp -o nombre nombre.c

    La clausula copyprivate establece que una o mas variables se deben compartir entre todos
    los subprocesos (misma variable compiada al resto de threads con el mismo nombre)

*/

#include <stdio.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num()
#endif

int main(){
    int n = 9 ,
        i,
        b[n];

    for(i=0;i<n;i++) b[i] = -1;

    printf("\nAntes de la sección parallel:\n");
    for(i=0;i<n;++i) printf("b[%d]=%d || ",i,b[i]);
    
    #pragma omp parallel
    {
        int a ;

        #pragma omp single copyprivate(a)
        {
            printf("\nIntroduce el valor de inicializacion a :");
            scanf("%d",&a);
            printf("Sección sigle ejecutada por el thread %d",omp_get_thread_num());
        }

        #pragma omp for
        for(i=0;i<n;i++) b[i] = a;
    }

    printf("\nDespues de la sección parallel:\n");
    for(i=0;i<n;++i) printf("b[%d]=%d || ",i,b[i]);

    return 0;
}