/*
    Nombre: Alejandro Molina Criado
    Fecha: 01 / 04 / 2020

    para compilar: gcc -O2 -fopenmp -o nombre nombre.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc , char **argv){
    int i,n = 20 , 
        a[n],
        suma = 0;

    if(argc < 2) {
        fprintf(stderr , "\nERROR:Falta iteraciones\n");
        exit(-1);
    }    

    n = atoi(argv[1]); if(n>20) n = 20;

    for(i = 0 ; i < n ; ++i)
        a[i] = i;

    #pragma omp parallel
    {
        int sumaLocal = 0; //Esta variable es privada dentro de esta seción parallel

        #pragma omp for schedule(static)
        for(i = 0 ; i < n ; ++i){
            sumaLocal += a[i]; //cada thread tiene su propia instancia de sumaLocal inicializada a 0
            printf("thread %d suma de a[%d]=%d || sumaLocal =  %d\n",
                    omp_get_thread_num(),i,a[i],sumaLocal);
        }

        #pragma omp atomic
            suma+=sumaLocal; //suma de forma segura cada una de las instancias sumaLocal

    }//<--Final región paralela

    printf("Fuera de parallel suma = %d \n" , suma);

    return 0;

}