#include "memory_manager.h"
#include <stdlib.h>

Block* alloumem(size_t size)
{
    Node* current_node = list.head;
    Block* block = NULL;

    while (current_node)
    {
        Block* current_block = (Block*)current_node->value;
	
	if (block->is_free)
	{
	    Block* free_block = NULL;

	    if (partition_block(current_block, &free_block, size))
	    {
	        if (free_block->size == 0)
		{
		    Node* next_node = current_node->next;
		    Node* new_node = malloc(sizeof(Node));
		
		    new_node->value = free_block;
	 	    new_node->next = next_node;
		    next_node = new_node;

	            block = current_block;
		}
	 	
		break;
	    }
	}
        
	current_node = current_node->next;
    }

    return block;
}
