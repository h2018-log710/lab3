#include "memory_manager.h"

Block* first_fit_alloumem(size_t size)
{
    Node* current_node = list.head;
    Block* current_block = NULL;
    
    while (current_node)
    {
        current_block = (Block*)current_node->value;
        
        if (current_block->is_free)
        {
            Block* free_block = NULL;
            
            if (partition_block(current_block, &free_block, size))
            {
                if (free_block->size != 0)
                {
                    Node* next_node = current_node->next;
                    Node* free_node = malloc(sizeof(Node));
                    
                    free_node->value = free_block;
                    free_node->next = next_node;
                    current_node->next = free_node;
                }
                
                break;
            }
        }
        
        current_node = current_node->next;
    }
    
    return current_block;
}
