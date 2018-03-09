#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "memory_manager.h"

void print_mem()
{
    const char alloc_c = 'X';
    const char free_c = 'O';
    char c[9] = {'\0'};

    for(int i = 0; i < TOTAL_MEMORY; i+=8)
    {
        for(int j = 0; j < 8; j++)
        {
            if(mem_est_alloue(i+j))
            {
                c[j] = alloc_c;
            }
            else
            {
                c[j] = free_c;
            }
        }
        
        printf("0x%02x  %s\n", i, c);
    }
}

int main(int argc, char* argv[])
{
    printf("Initialisation ");
    initmem();
    
    printf("[Blocs libres: %d Blocs alloues: %d]\n", nbloclibres(), nblocalloues());
    printf("[Memoire libre: %d Taille bloc libre eleve: %d]\n", memlibre(), mem_pgrand_libre());
    print_mem();
    
    printf("Allocation ");    
    first_fit_alloumem(8);
    first_fit_alloumem(8);
    printf("[Blocs libres: %d Blocs alloues: %d]\n", nbloclibres(), nblocalloues());
    printf("[Memoire libre: %d Taille bloc libre eleve: %d]\n", memlibre(), mem_pgrand_libre());
    print_mem();
    
    return 0;
}
