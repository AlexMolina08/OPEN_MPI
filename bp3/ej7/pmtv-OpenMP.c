/*
    *   Alejandro Molina Criado
    *   BP3 Arquitectura de Computadores
    *   06/05/2020
    *   Para compilar : gcc -O2 -fopenmp -o if-clausule-modificado if-clausule-modificado.c
*/
#include <stdlib.h>
#include <stdio.h> 
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
    #define omp_get_num_threads() 1
    #define omp_set_num_threads(int)
    #define omp_in_parallel() 0
    #define omp_set_dynamic(int)
#endif

int main(int argc, char** argv){
    double t_ini, t_final, t_total;

    if (argc<2){
        printf("Faltan no componentes del vector\n");
        exit(-1);
    }

    int i, j;
    int *v, *mv, **m;
    unsigned int N = atoi(argv[1]); 

    v = (int*) malloc(N*sizeof(int));
    mv = (int*) malloc(N*sizeof(int));
    m = (int **)malloc(N*sizeof(int *));

    for (i=0;i<N;i++)
        m[i] = (int *) malloc (N*sizeof(int));

    if ( v==NULL || mv==NULL || m==NULL ){
        printf("Error en la reserva de espacio para la matriz y el vector\n");
        exit(-2);
    }

    for(i=0; i<N; i++)
        if(m[i] == NULL){
            printf("Error en la reserva de espacio para la matriz y el vector\n");
            exit(-3);
        }

    #pragma omp parallel for schedule(runtime)
    for(i=0; i<N; i++){
        for(j=i; j<N; j++){
            m[i][j] = 9;
        }

        v[i] = 2;
        mv[i] = 0;
    }

    t_ini = omp_get_wtime();
    #pragma omp parallel for schedule(runtime)
    for(i=0; i<N; i++){
        for(j=i; j<N;j++){
            mv[i] += m[i][j] * v[i];
        }
    }

    t_final = omp_get_wtime();
    t_total = t_final - t_ini;


    printf("Tamaño de la matriz y vector:%d\t / Tiempo(seg.) %11.9f\n", N, t_total);
    for(i=0; i<N; i++)
        free(m[i]);
    free(mv);
    free(m);
    free(v);

    return 0;
}