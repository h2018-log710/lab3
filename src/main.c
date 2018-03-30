#include <stdlib.h>
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

AllocationStrategy get_allocation_stategy(char* strategy_str)
{
    if (!strcmp(strategy_str, "first_fit"))
    {
        return AS_FIRST_FIT;
    }  
    else if (!strcmp(strategy_str, "best_fit"))
    {
        return AS_BEST_FIT;
    }  
    else if (!strcmp(strategy_str, "worst_fit"))
    {
        return AS_WORST_FIT;
    }
    else if (!strcmp(strategy_str, "next_fit"))
    {
        return AS_NEXT_FIT;
    }
    return AS_INVALID;
}

int main(int argc, char* argv[])
{
    int count = 0;
    char buff[255];
    char* parse_output = NULL;
    char* args[255];
    Block* block = NULL;
    
    initmem();
        
    while (true)
    {
        printf("lab3> ");
        fgets(buff, 255, stdin);

        if(buff[0] != '\n')
        {
            count = 0;
            strtok(buff, "\n");
            parse_output = strtok(buff, " ");
            while (parse_output != NULL)
            {
                args[count++] = parse_output;
                parse_output = strtok(NULL, " ");
            }

            if (strcmp(args[0], "exit") == 0)
            {
                break;
            }
            else if (strcmp(args[0], "alloumem") == 0 && count == 3)
            {
                block = alloumem(strtol(args[1], NULL, 0), get_allocation_stategy(args[2]));
                if (block)
                {
                    printf("Bloc à l'adresse %p alloue.\n", block);
                }
                else
                {
                    printf("Impossible d'allouer le bloc\n");
                }

            }
            else if (strcmp(args[0], "liberemem") == 0 && count == 2)
            {
                liberemem((void*) strtol(args[1], NULL, 0));
            }
            else if (strcmp(args[0], "affiche_etat_memoire") == 0)
            {
                affiche_etat_memoire();
            }
            else if (strcmp(args[0], "affiche_parametres_memoire") == 0)
            {
                affiche_parametres_memoire();
            }
            else
            {
                printf("Commande invalide\n");
            }
        }
    }
    return 0;
}
