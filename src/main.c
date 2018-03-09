#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "memory_manager.h"

int main(int argc, char* argv[])
{
    printf("Initialisation ");
    initmem();
    
    printf("[Blocs libres: %d Blocs alloues: %d]\n", nbloclibres(), nblocalloues());
    printf("[Memoire libre: %d Taille bloc libre eleve: %d]\n", memlibre(), mem_pgrand_libre());
    
    printf("Allocation ");    
    alloumem(sizeof(int));
    
    printf("[Blocs libres: %d Blocs alloues: %d]\n", nbloclibres(), nblocalloues());
    printf("[Memoire libre: %d Taille bloc libre eleve: %d]\n", memlibre(), mem_pgrand_libre());
    
    return 0;
}
