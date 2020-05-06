/*
    *   Alejandro Molina Criado
    *   BP3 Arquitectura de Computadores
    *   06/05/2020
    *   Para compilar : gcc -O2 -fopenmp -o if-clausule-modificado if-clausule-modificado.c
*/

#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif

int main(int argc, char ** argv){
    int i, n = 200, chunk, a[n], suma = 0, modif;
    omp_sched_t tipo;

    if(argc < 3){
        fprintf(stderr,"\nFalta iteraciones o chunk \n");
        exit(-1);
    }

    n = atoi(argv[1]);
    if(n>200) n=200;
    chunk = atoi(argv[2]);

    int dyn_var = omp_get_dynamic();
    int nthreads_var = omp_get_max_threads();
    int thread_limit_var = omp_get_thread_limit();
    omp_get_schedule(&tipo, &modif); 

    for(i=0; i<n; i++) a[i]=i;

    #pragma omp parallel for firstprivate(suma) lastprivate(suma) schedule(dynamic, chunk)
        for(i=0;i<n;i++){
            suma = suma + a[i];
            printf("thread %d suma a[%d] suma=%d \n", omp_get_thread_num(), i, suma);
        }

        #pragma omp single
            printf("\nthread %d imprime dyn-var %d \n", omp_get_thread_num(), dyn_var);
            printf("thread %d imprime nthreads-var %d \n", omp_get_thread_num(), nthreads_var);
            printf("thread %d imprime thread-limit-var %d \n", omp_get_thread_num(),thread_limit_var);
            printf("thread %d imprime run-sched-var mod %d \n", omp_get_thread_num(), modif);
            if(tipo == omp_sched_static) printf("El tipo es estático \n");
            if(tipo == omp_sched_dynamic) printf("El tipo es dinámico \n");
            if(tipo == omp_sched_guided) printf("El tipo es guided \n");

        printf("\nFuera de 'parallel for' suma %d\n dyn-var %d\n nthreads-var %d\n thread-limit-var %d\
n run-sched-var mod %d\n",suma,dyn_var, nthreads_var, thread_limit_var, modif);

        if(tipo == omp_sched_static) printf("El tipo es estático \n");
        if(tipo == omp_sched_dynamic) printf("El tipo es dinámico \n");
        if(tipo == omp_sched_guided) printf("El tipo es guided \n");
}