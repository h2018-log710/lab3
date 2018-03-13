#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "memory_manager.h"

void print_mem()
{
    const char alloc_c = 'X';
    const char free_c = 'O';
    char c1[5] = {'\0'};
    char c2[5] = {'\0'};

    for (int i = 0; i < TOTAL_MEMORY; i+=8)
    {
        for (int j = 0; j < 4; j++)
        {
            if (mem_est_alloue(i+j))
            {
                c1[j] = alloc_c;
            }
            
            else
            {
                c1[j] = free_c;
            }
        }
        
        for (int j = 4; j < 8; j++)
        {
            if (mem_est_alloue(i+j))
            {
                c2[j-4] = alloc_c;
            }
            
            else
            {
                c2[j-4] = free_c;
            }
        }
        
        printf("0x%04x  %s %s\n", i, c1, c2);
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
    Block* a = alloumem(2, BEST_FIT);
    //Block* b = alloumem(5, FIRST_FIT);
    //Block* c = alloumem(3, FIRST_FIT);
    //Block* d = alloumem(2, FIRST_FIT);
    //liberemem(a);
    //liberemem(b);
    printf("[Blocs libres: %d Blocs alloues: %d]\n", nbloclibres(), nblocalloues());
    printf("[Memoire libre: %d Taille bloc libre eleve: %d]\n", memlibre(), mem_pgrand_libre());
    print_mem();
    
    return 0;
}
