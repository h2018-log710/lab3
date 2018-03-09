#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include "list.h"

#define TOTAL_MEMORY 0x100

extern List list;

typedef struct Block
{
    size_t size;
    intptr_t address;
    bool is_free;
} Block;

void dbg_print_list_addr();

bool partition_block(Block* alloc_block, Block** free_block, size_t alloc_size);
Node* create_node(size_t size, uintptr_t address, bool is_free);
void free_node(Node* node);
void initmem();
void liberemem(void* pBloc);
int nbloclibres();
int nblocalloues();
int memlibre();
int mem_pgrand_libre();
int mem_small_free(int maxTaillePetit);
bool mem_est_alloue(void* pOctet);

Block* first_fit_alloumem(size_t size);
Block* best_fit_alloumem(size_t size);
Block* worst_fit_alloumem(size_t size);
Block* next_fit_alloumem(size_t size);

#endif
