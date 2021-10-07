#include "omp.h"

#include <stdio.h>
#include <stdlib.h>
 
void main()
{
 
    // Beginning of parallel region
    #pragma omp parallel
    {
 
        printf("Hello World... from thread = %d\n", omp_get_thread_num());
    }
    // Ending of parallel region


    printf("\n");

    int tsum=0;
    #pragma omp parallel
    {
        tsum += omp_get_thread_num();
    }    
    printf("Sum is %d\n",tsum);
    
}
