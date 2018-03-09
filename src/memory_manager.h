#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include "list.h"

#define TOTAL_MEMORY 1024

extern List list;

typedef struct Block
{
    size_t size;
    intptr_t address;
    bool is_free;
} Block;

bool partition_block(Block* alloc_block, Block** free_block, size_t alloc_size);
void initmem();
Block* alloumem(size_t size);
void liberemem(void* pBloc);
int nbloclibres();
int nblocalloues();
int memlibre();
int mem_pgrand_libre();
int mem_small_free(int maxTaillePetit);
bool mem_est_alloue(void* pOctet);

#endif
