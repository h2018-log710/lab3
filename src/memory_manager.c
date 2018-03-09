#include "memory_manager.h"
#include <stdlib.h>

List list;

bool partition_block(Block* alloc_block, Block** free_block, size_t alloc_size)
{
   if (alloc_block->size >= alloc_size)
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
    list.head = create_node(TOTAL_MEMORY, 0x0, true);
}

void liberemem(void* pBloc)
{
    
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

int mem_small_free(int maxTaillePetit)
{
    return 0;
}

bool mem_est_alloue(void* pOctet)
{
    return false;
}
