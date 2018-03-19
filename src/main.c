#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "memory_manager.h"

void affiche_etat_memoire()
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

void affiche_parametres_memoire()
{
    printf("[Blocs libres: %d Blocs alloues: %d]\n", nbloclibres(), nblocalloues());
    printf("[Memoire libre: %d Taille bloc libre eleve: %d]\n", memlibre(), mem_pgrand_libre());
    printf("[Blocs libres plus petits que %d: %d]\n", TOTAL_MEMORY, mem_small_free(TOTAL_MEMORY));
}

AllocationStrategy validate_arguments(int argc, char* argv[])
{
    if (argc >= 2)
    {
        if (!strcmp(argv[1], "first_fit"))
        {
            return AS_FIRST_FIT;
        }
        
        else if (!strcmp(argv[1], "best_fit"))
        {
            return AS_BEST_FIT;
        }
        
        else if (!strcmp(argv[1], "worst_fit"))
        {
            return AS_WORST_FIT;
        }
        
        else if (!strcmp(argv[1], "next_fit"))
        {
            return AS_NEXT_FIT;
        }
    }
    
    return AS_INVALID;
}

int main(int argc, char* argv[])
{
    AllocationStrategy alloc_strategy = validate_arguments(argc, argv);
    
    if (alloc_strategy != AS_INVALID)
    {
        initmem();
        
        affiche_parametres_memoire();
        affiche_etat_memoire();
        printf("\n");
        
        Block* a = alloumem(4, alloc_strategy);
        affiche_parametres_memoire();
        affiche_etat_memoire();
        printf("\n");
        
        liberemem(a);
        Block* b = alloumem(8, alloc_strategy);
        affiche_parametres_memoire();
        affiche_etat_memoire();
        printf("\n");

        Block* c = alloumem(4, alloc_strategy);
        affiche_parametres_memoire();
        affiche_etat_memoire();
        printf("\n");

        Block* d = alloumem(8, alloc_strategy);
        affiche_parametres_memoire();
        affiche_etat_memoire();
        printf("\n");

        liberemem(c);
        Block* e = alloumem(4, alloc_strategy);
        affiche_parametres_memoire();
        affiche_etat_memoire();
        printf("\n");
        
        liberemem(b);
        liberemem(d);
        liberemem(e);
        
        return 0;
    }
    
    printf("Arguments invalides.\n");
    
    return -1;
}
