#include <stdio.h>
#include <omp.h>

int main(void){

    #pragma omp parallel
    printf("(%d:Hola )" , omp_get_thread_num());
    #pragma omp parallel
    printf("(%d:mundo!)" , omp_get_thread_num());
    return (0);
}
