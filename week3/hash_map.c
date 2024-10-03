#include <stdio.h>
#include <stdlib.h>
#include "hash_map_internal_linked_list.h"

struct HashMap {
    LinkedList* array;
    DataType key_data_type;
    DataType value_data_type;
    DataType (*set_key)(void*);
    DataType (*get_key)(void*);
};

void int_int_set_key(void* key, void* value) {
    // this should use a generic
}

int int_int_get_key(void* key) {
    return 3;
}



void main() {

    return;
}