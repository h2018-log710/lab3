#include <stdlib.h>

#include "memory_manager.h"

Block* best_fit_alloumem(size_t size)
{
    Node* current_node = list.head;
    Node* candidate_node = NULL;

    while (current_node)
    {
        Block* current_block = (Block*)current_node->value;
    
        if (current_block->is_free &&
            current_block->size >= size &&
            (!candidate_node ||
            (candidate_node && current_block->size < ((Block*)candidate_node->value)->size)))
        {
            candidate_node = current_node;
        }
        
        current_node = current_node->next;
    }

    if(candidate_node)
    {
        Block* candidate_block = candidate_node->value;
        Block* free_block = NULL;

        if (partition_block(candidate_block, &free_block, size))
        {
            if (free_block->size == 0)
            {
                Node* next_node = candidate_node->next;
                Node* new_node = malloc(sizeof(Node));
        
                new_node->value = free_block;
                new_node->next = next_node;
                next_node = new_node;
            }
            return candidate_block;
        }
    }
    return NULL;
}
