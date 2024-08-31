// math_operations.h

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
} DataType;

typedef struct LinkedList {
    void* value;
    DataType data_type;
    struct LinkedList* next;
} LinkedList;
size_t node_data_type_size(DataType data_type);
void print_node_value(struct LinkedList* node);
void init_generic_linked_list_node(struct LinkedList* linked_list, void* value, DataType data_type);
void traversal_func(struct LinkedList* obj);
struct LinkedList* pop(struct LinkedList** obj);
void unshift(struct LinkedList** obj, void* value, DataType data_type);
void append(struct LinkedList** obj, void* value, DataType data_type);
void invert_list(struct LinkedList** root);

#endif
