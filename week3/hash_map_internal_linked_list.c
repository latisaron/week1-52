// holy fuck this is a lot of boilerplate
#include <stdio.h>
#include <stdlib.h>
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

size_t node_data_type_size(DataType data_type) {
    switch (data_type) {
        case TYPE_INT :
            return sizeof(int);
        case TYPE_FLOAT :
            return sizeof(float);
        case TYPE_CHAR :
            return sizeof(char);
        default:
            return sizeof(int);
    }
}

void print_node_value(struct LinkedList* node) {
    if (node != NULL) {
        switch (node->value_data_type) {
            case TYPE_INT :
                printf("%d", *(int *)(node->value));
                break;
            case TYPE_FLOAT :
                printf("%f", *(float *)(node->value));
                break;
            case TYPE_CHAR :
                printf("%c", *(char *)(node->value));
                break;
            default:
                printf("%d", *(int *)(node->value));
                break;
        }
    } else {
        printf("empty node");
    }
    return;
}

void init_generic_linked_list_node(struct LinkedList* linked_list, void* key, DataType key_data_type, void *value, DataType value_data_type) {
    linked_list->value = malloc(node_data_type_size(value_data_type));
    if (linked_list->value == NULL) {
        printf("failed to allocate memory");
        return;
    }
    linked_list->value_data_type = value_data_type;
    memcpy(linked_list->value, value, node_data_type_size(value_data_type));

    linked_list->key = malloc(node_data_type_size(key_data_type));
    if (linked_list->key == NULL) {
        printf("failed to allocate memory");
        return;
    }
    linked_list->key_data_type = key_data_type;
    memcpy(linked_list->key, key, node_data_type_size(key_data_type));
}

struct LinkedList* pop(struct LinkedList** obj) {
    if (*obj == NULL) {
        printf("cannot pop anymore, list is empty \n");
        return NULL;
    }
    struct LinkedList* cur = *obj;
    struct LinkedList* prev = *obj;
    while (cur->next != NULL) {
        prev = cur;
        cur = cur->next;
    }
    prev->next = NULL;

    if (cur == *obj) {
        *obj = NULL;
    }
    return cur;
};

void unshift(struct LinkedList** obj, void* key, DataType key_data_type, void *value, DataType value_data_type) {
    struct LinkedList* new_node = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    init_generic_linked_list_node(new_node, key, key_data_type, value, value_data_type);
    new_node->next = *obj;
    *obj = new_node;
    return;
};

void append(struct LinkedList** obj, void* key, DataType key_data_type, void *value, DataType value_data_type) {
    struct LinkedList* cur = *obj;
    struct LinkedList* empty_pointer = NULL;
    struct LinkedList* new_node = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    init_generic_linked_list_node(new_node, key, key_data_type, value, value_data_type);
    new_node->next = empty_pointer;
    if (*obj == NULL) {
        *obj = new_node;
    } else {
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = new_node;
    }
    return;
};