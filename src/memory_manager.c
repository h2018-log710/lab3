#include "memory_manager.h"
#include <stdio.h>
#include <stdlib.h>

List list;

void dbg_print_list_addr()
{
    Node* current_node = list.head;
    
    while (current_node)
    {
        printf("node:%p block:%p is_free:%d\n", current_node, current_node->value, ((Block*)current_node->value)->is_free);
        current_node = current_node->next;
    }
}

bool partition_block(Block* alloc_block, Block** free_block, size_t alloc_size)
{
   if (alloc_block->size >= alloc_size)
   {
       *free_block = malloc(sizeof(Block));
       
       (*free_block)->size = alloc_block->size - alloc_size;
       (*free_block)->address = alloc_block->address + alloc_size;
       (*free_block)->is_free = true;
       alloc_block->size = alloc_size;
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
    if(node == last_fitted_Node)
    {
        last_fitted_Node = last_fitted_Node->next;
    }

    free(node->value);
    list_remove(&list, node);
}

void initmem()
{
    list.head = create_node(TOTAL_MEMORY, 0x0, true);
}

Block* alloumem(size_t size, AllocationStrategy alloc_strategy)
{
    switch (alloc_strategy)
    {
        case AS_FIRST_FIT:
            return first_fit_alloumem(size);
        case AS_BEST_FIT:
            return best_fit_alloumem(size);
        case AS_WORST_FIT:
            return worst_fit_alloumem(size);
        case AS_NEXT_FIT:
            return next_fit_alloumem(size);
        default:
            return NULL;
    }
}

void liberemem(Block* pBloc)
{
    Node* current_node = list.head;
    Block* previous_block = NULL;
    Block* current_block = NULL;
    
    while (current_node)
    {
        current_block = (Block*)current_node->value;
        
        if (current_block == pBloc)
        {
            Block* next_block = current_node->next ? current_node->next->value : NULL;
            bool merged = false;
            
            if (next_block && next_block->is_free)
            {
                // We extend the current block.
                current_block->size += next_block->size;
                current_block->is_free = true;
                
                // The next node is elected to be removed.
                free_node(current_node->next);
                merged = true;
            }
            
            if (previous_block && previous_block->is_free)
            {
                // We extend the previous free block.
                previous_block->size += current_block->size;
                
                // The current node is elected to be removed.
                free_node(current_node);
                merged = true;
            }
            
            if (!merged)
            {
                // There is no free block around.
                current_block->is_free = true;
            }
            
            break;
        }
        
        previous_block = current_node->value;
        current_node = current_node->next;
    }
}

int nbloclibres()
{
    Node* current_node = list.head;
    int num_free_blocks = 0;
    
    while (current_node)
    {
        Block* current_block = (Block*)current_node->value;
        
        if (current_block->is_free)
        {
            ++num_free_blocks;
        }
        
        current_node = current_node->next;
    }
    
    return num_free_blocks;
}

int nblocalloues()
{
    Node* current_node = list.head;
    int num_alloc_blocks = 0;
    
    while (current_node)
    {
        Block* current_block = (Block*)current_node->value;
        
        if (!current_block->is_free)
        {
            ++num_alloc_blocks;
        }
        
        current_node = current_node->next;
    }
    
    return num_alloc_blocks;
}

int memlibre()
{
    Node* current_node = list.head;
    int num_free_mem = 0;
    
    while (current_node)
    {
        Block* current_block = (Block*)current_node->value;
        
        if (current_block->is_free)
        {
            num_free_mem += current_block->size;
        }
        
        current_node = current_node->next;
    }
    
    return num_free_mem;
}

int mem_pgrand_libre()
{
    Node* current_node = list.head; 
    int num_free_highest_mem = 0;
    
    while (current_node)
    {
        Block* current_block = (Block*)current_node->value;
        
        if (current_block->is_free && current_block->size > num_free_highest_mem)
        {
            num_free_highest_mem = current_block->size;
        }
        
        current_node = current_node->next;
    }
    
    return num_free_highest_mem;
}

int mem_small_free(size_t maxTaillePetit)
{
    Node* current_node = list.head;
    int num_free_small_blocks = 0;
    
    while (current_node)
    {
        Block* current_block = (Block*)current_node->value;
        
        if (current_block->is_free && current_block->size < maxTaillePetit)
        {
            ++num_free_small_blocks;
        }
        
        current_node = current_node->next;
    }
    
    return num_free_small_blocks;
}

bool mem_est_alloue(intptr_t pOctet)
{
    Node* current_node = list.head;
    Block* current_block = NULL;
    
    while (current_node)
    {
        current_block = (Block*)current_node->value;
        
        if (current_block->address + current_block->size > pOctet)
        {
            return !current_block->is_free;
        }
        
        current_node = current_node->next;
    }
    
    return false;
}
