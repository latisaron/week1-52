#include <stdio.h>
#include <stdlib.h>
#include "../week2/linked_list.h"

struct IntIntHashMap {
    int* array;
    unsigned int cursize;
    void (*set_key)(int, int);
    int (*get_key)(int);
};

void int_int_set_key(int key, int value) {
    // this should use a generic
}

int int_int_get_key(int key) {
    return 3;
}

void main() {

    return;
}