/*
    Nombre: Alejandro Molina Criado
    Fecha: 01 / 04 / 2020

    para compilar: gcc -O2 -fopenmp -o nombre nombre.c

    Con la cláusula atomic asegura la exclusión mutua en una región de memoria
*/

#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num()
#endif

int main(int argc , char **argv){
    int i,
        n = 20,
        a[n],
        suma = 0;
    if (argc < 2){
        fprintf(stderr,"ERROR: Faltan iteraciones\n");
        exit(-1);
    }
    n = atoi(argv[1]); 
    if(n > 20){
        n = 20;
        printf("n = %d" ,n);
    }
    for(i = 0 ; i < n ; ++i) a[i] = i;
    
    #pragma omp parallel for 
    for(i=0;i<n;++i){ 
        #pragma omp atomic
        suma+=a[i];
    }

    printf("\nFinal de la sección parralel , suma = %d\n" , suma);

    return 0;
}