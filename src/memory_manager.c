#include "memory_manager.h"
#include <stdlib.h>

List list;

bool partition_block(Block* alloc_block, Block** free_block, size_t alloc_size)
{
   if (alloc_block->size <= alloc_size)
   {
       *free_block = malloc(sizeof(Block));
       
       (*free_block)->size = alloc_block->size - alloc_size;
       (*free_block)->address = alloc_block->address + alloc_size;
       (*free_block)->is_free = true;
       alloc_block->is_free = false;

       return true;
   }

   return false;
}

Node* create_node(size_t size, uintptr_t address, bool is_free)
{
    Node* node = malloc(sizeof(Node));
    Block* block = malloc(sizeof(Block));
    
    block->size = size;
    block->address = address;
    block->is_free = is_free;
    
    node->value = block;
    node->next = NULL;

    return node;
}

void free_node(Node* node)
{
    free(node->value);
    free(node);
}

void initmem()
{
    Node* node = create_node(TOTAL_MEMORY, 0x0, true);
    list_push_back(&list, node);
}

void liberemem(void* pBloc)
{
    
}

int nbloclibres()
{
    
}

int nblocalloues()
{
    
}

int memlibre()
{
    
}

int mem_pgrand_libre()
{
    
}

int mem_small_free(int maxTaillePetit)
{
    
}

bool mem_est_alloue(void* pOctet)
{
    Node* current_node = list.head;
    Block* current_block = NULL;

    while (current_node)
    {
        current_block = (Block*)current_node->value;
    
        if (current_block->address >= pOctet && 
           (current_block->address + current_block->size) < pOctet)
        {
            return !current_block->is_free;
        }
        
        current_node = current_node->next;
    }

    return false;
}
