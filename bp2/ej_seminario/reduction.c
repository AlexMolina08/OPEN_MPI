/*
    Nombre: Alejandro Molina Criado
    Fecha: 01 / 04 / 2020

    para compilar: gcc -O2 -fopenmp -o nombre nombre.c

    Con la cláusula reduction estblecemos que una o más variables , privadas para cada subproceso,
    se juntan al final de cada region paralela.
*/

#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num()
#endif

int main(int argc , char **argv){
    int i,n = 20,
        a[n],
        suma = 0;
    

    if (argc < 2){
        fprintf(stderr,"Faltan iteraciones\n");
        exit(-1);
    }

    n = atoi(argv[1]); 

    if(n > 20){
        n = 20;
        printf("n = %d" ,n);
    }

    for(i = 0 ; i < n ; ++i) a[i] = i;

    #pragma omp parallel for reduction(+:suma) 
    for(i=0;i<n;++i){ 
        suma+=a[i];
        printf("suma = %d || thread: %d\n", suma , omp_get_thread_num());
    }

    printf("\nsuma = %d\n" , suma);

    return 0;
}