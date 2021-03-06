/*
    Nombre: Alejandro Molina Criado
    Fecha: 08 / 04 / 2020

    para compilar: gcc -O2 -fopenmp -o nombre nombre.c

    La cláusula shared establece que una o más variables se deben compartir 
    entre todos los procesos
*/

#include <stdio.h>

//directiva para el compilador
#ifdef _OPENMP
    #include <omp.h>
#endif

int main(){

    int i , n = 8 , 
        a[n];
    
    for(i = 0 ; i < n ; ++i)
        a[i] = i + 1;
    
    #pragma omp parallel for shared(a,n) , default(none)
    for(i=0;i<n;++i){   
        a[i]+=i; //[1+0,2+1,3+2,....]
    }

    printf("Fin de la sección parallel for:\n");

    for(i = 0 ; i < n ; ++i)
        printf("a[%d] = %d || ",i,a[i]);
    printf("\n");
    
    return 0;
}





