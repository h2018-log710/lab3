#include "list.h"
#include <stdlib.h>

bool list_empty(const List* list)
{
    if (list->head)
    {
        return true;
    }
    
    return false;
}

Node* list_front(List* list)
{
    if (list)
    {
        return list->head;
    }
    
    return NULL;
}

void list_insert_after(List* list, void* value, Node* node)
{
    if (list && node)
    {
        Node* current_node = list->head;
        
        while (current_node)
        {
            if (current_node == node)
            {
                Node* new_node = malloc(sizeof(Node));
                
                new_node->value = value;
                new_node->next = current_node->next;
                current_node->next = new_node;
                
                break;
            }
            
            current_node = current_node->next;
        }
    }
}

void list_remove(List* list, Node* node)
{
    if (list && node)
    {
        Node* current_node = list->head;
        Node* previous_node = NULL;
        
        while (current_node)
        {
            if (current_node == node)
            {
                if (current_node == list->head)
                {
                    list->head = current_node->next;
                }
                
                if (previous_node)
                {
                    previous_node->next = current_node->next;
                }
                
                current_node->value = NULL;
                free(current_node);
                
                break;
            }

            previous_node = current_node;
            current_node = current_node->next;
        }
    }
}
