
#include <stdio.h>
#include <omp.h>

int main(void){

    #pragma omp parallel
    printf("(%d:Hola mundo!)" , omp_get_thread_num());
	printf("\n");
    return (0);
}
