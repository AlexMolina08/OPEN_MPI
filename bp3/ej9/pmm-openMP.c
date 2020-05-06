/*
    *   Alejandro Molina Criado
    *   BP3 Arquitectura de Computadores
    *   06/05/2020
    *   Para compilar : gcc -O2 -fopenmp -o if-clausule-modificado if-clausule-modificado.c
*/

#include <stdlib.h> 
#include <stdio.h> // biblioteca donde se encuentra la función printf()
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
    int i, j, k;
    double t_ini, t_fin, t_total;

    if (argc<2){
        printf("ERROR: Faltan no componentes del vector\n");
        exit(-1);
    }

    unsigned int N = atoi(argv[1]); // Máximo N =2^32-1=4294967295 (sizeof(unsigned int) = 4 B)

        int **mr, **m1, **m2;
    m1 = (int **) malloc(N*sizeof(int *));
    m2 = (int **) malloc(N*sizeof(int *));
    mr = (int **) malloc(N*sizeof(int *));

    for (i=0;i<N;i++){
        mr[i] = (int *) malloc (N*sizeof(int));
        m1[i] = (int *) malloc (N*sizeof(int));
        m2[i] = (int *) malloc (N*sizeof(int));
    }

    if ( mr==NULL || m1==NULL || m2==NULL ){
        printf("Error en la reserva de espacio para la matriz y el vector\n");
        exit(-2);
    }

    for(i=0; i<N; i++)
        if(mr[i] == NULL || m1[i] == NULL || m2[i] == NULL){
            printf("Error en la reserva de espacio para la matriz y el vector\n");
            exit(-3);
        }

    #pragma omp parallel for private(j)
    for(i=0; i<N; i++){
        for(j=i; j<N; j++){
            mr[i][j] = 0;
            m1[i][j] = 2+i;
            m2[i][j] = 2+i;
        }
    }


    t_ini = omp_get_wtime();
    
    #pragma omp parallel for private(j,k)
    for(i=0; i<N; i++){
        for(j=0; j<N;j++){
            for(k=0; k<N; k++){
                mr[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }   

    t_fin = omp_get_wtime();
    t_total = t_fin - t_ini;


    printf("Tamaño de la matriz y vector:%d\t / Tiempo(seg.) %11.9f\n", N, t_total);
    printf("Tiempo = %11.9f\t Primera línea= %d\t Última línea= %d\n", t_total, mr[0][0], mr[N-1][N-1]);

    return 0;
}
