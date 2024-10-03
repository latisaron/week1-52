// math_operations.h

#ifndef HASH_MAP_INTERNAL_LINKED_LIST_H
#define HASH_MAP_INTERNAL_LINKED_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
} DataType;

typedef struct LinkedList {
    void* key;
    void* value;
    DataType key_data_type;
    DataType value_data_type;
    struct LinkedList* next;
} LinkedList;
size_t node_data_type_size(DataType data_type);
void print_node_value(struct LinkedList* node);
void init_generic_linked_list_node(struct LinkedList* linked_list, void* key, DataType key_data_type, void *value, DataType value_data_type);
struct LinkedList* pop(struct LinkedList** obj);
void unshift(struct LinkedList** obj, void* key, DataType key_data_type, void *value, DataType value_data_type);
void append(struct LinkedList** obj, void* key, DataType key_data_type, void *value, DataType value_data_type);

#endif
