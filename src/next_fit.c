#include "memory_manager.h"
#include <stdlib.h>
#include <stdio.h>

Node* last_fitted_Node = NULL;

Block* next_fit_alloumem(size_t size)
{
    if (last_fitted_Node == NULL)
    {
        last_fitted_Node = list.head;
    }

    Node* current_node = last_fitted_Node;
    Block* current_block = NULL;
    
    do
    {
        current_block = (Block*)current_node->value;
        
        if (current_block->is_free)
        {
            Block* free_block = NULL;
            
            if (partition_block(current_block, &free_block, size))
            {
                if (free_block->size != 0)
                {
                    list_insert_after(&list, free_block, current_node);
                }
                
                break;
            }
        }

        if(current_node->next == NULL)
        {
            // we wrap around the list
            current_node = list.head;
        }
        else
        {
            current_node = current_node->next;
        }
    }
    while (current_node != last_fitted_Node);

    last_fitted_Node = current_node->next;
    return current_block;
}
