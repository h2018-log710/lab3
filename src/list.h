#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Node
{
    void* value;
    struct Node* next;
} Node;

typedef struct List
{
    struct Node* head;
} List;

bool list_empty(const List* list);
void list_insert_after(List* list, void* value, Node* node);
void list_remove(List* list, Node* node);

#endif
