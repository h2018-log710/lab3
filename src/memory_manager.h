#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stdbool.h>
#include <stdint.h>

#include "first_fit.h"
#include "best_fit.h"
#include "worst_fit.h"
#include "next_fit.h"

typedef struct Block
{
    size_t size;
    intptr_t address;
    bool is_free;
} Block;

void initmem();
void* pBloc alloumem();
void liberemem(void* pBloc);
int nbloclibres();
int nblocalloues();
int memlibre();
int mem_pgrand_libre();
int mem_small_free(int maxTaillePetit);
bool mem_est_alloue(void* pOctet);

#endif
