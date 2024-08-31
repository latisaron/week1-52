// holy fuck this is a lot of boilerplate
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
} DataType;

struct LinkedList {
    void* value;
    DataType data_type;
    struct LinkedList* next;
};

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
        switch (node->data_type) {
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

void init_generic_linked_list_node(struct LinkedList* linked_list, void* value, DataType data_type) {
    linked_list->value = malloc(node_data_type_size(data_type));
    if (linked_list->value == NULL) {
        printf("failed to allocate memory");
        return;
    }
    linked_list->data_type = data_type;
    memcpy(linked_list->value, value, node_data_type_size(data_type));
}

void traversal_func(struct LinkedList* obj) {
    struct LinkedList* cur = obj;
    if (obj == NULL) {
        printf("bad bad cant traverse emtpy \n");
        return;
    }
    while (cur->next != NULL) {
        print_node_value(cur);
        printf("\n");
        cur = cur->next;
    }
    print_node_value(cur);
    printf("\n");
    printf("---------------\n");
};

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

void unshift(struct LinkedList** obj, void* value, DataType data_type) {
    struct LinkedList* new_node = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    init_generic_linked_list_node(new_node, value, data_type);
    new_node->next = *obj;
    *obj = new_node;
    return;
};

void append(struct LinkedList** obj, void* value, DataType data_type) {
    struct LinkedList* cur = *obj;
    struct LinkedList* empty_pointer = NULL;
    struct LinkedList* new_node = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    init_generic_linked_list_node(new_node, value, data_type);
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

void invert_list(struct LinkedList** root) {
    struct LinkedList* prev2 = NULL;
    struct LinkedList* prev1 = NULL;
 
    if (root != NULL) {
        while ((*root)->next != NULL) {
            if (prev1 != NULL) {
                prev1->next = prev2;
            }
            prev2 = prev1;
            prev1 = *root;
            *root = (*root)->next;
        }
        if (prev1 != NULL) {
            prev1->next = prev2;
            (*root)->next = prev1;
        }
    }
    return;
}


void main() {
    struct LinkedList* empty_pointer = NULL;

    struct LinkedList* aron = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    struct LinkedList* clau = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    struct LinkedList* ener = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    struct LinkedList* root = (struct LinkedList*)malloc(sizeof(struct LinkedList));

    int newval = 4;

    init_generic_linked_list_node(aron, &newval, TYPE_INT);
    aron->next= empty_pointer;
    print_node_value(aron);
        
    newval = 3;
    init_generic_linked_list_node(clau, &newval, TYPE_INT);
    clau->next= aron;
    
    newval = 2;
    init_generic_linked_list_node(ener, &newval, TYPE_INT);
    ener->next= clau;

    newval = 1;
    init_generic_linked_list_node(root, &newval, TYPE_INT);
    root->next= ener;
        

    traversal_func(root);
    void* last_popped;
    
    last_popped = pop(&root);
    printf("last popped is ");
    print_node_value(last_popped);
    printf("\n");
    free(last_popped);

    last_popped = pop(&root);
    printf("last popped is ");
    print_node_value(last_popped);
    printf("\n");
    free(last_popped);

    last_popped = pop(&root);
    printf("last popped is ");
    print_node_value(last_popped);
    printf("\n");
    free(last_popped);

    last_popped = pop(&root);
    printf("last popped is ");
    print_node_value(last_popped);
    printf("\n");
    free(last_popped);

    last_popped = pop(&root);
    printf("last popped is ");
    print_node_value(last_popped);
    printf("\n");
    free(last_popped);

    traversal_func(root);
    
    newval = 5;
    append(&root, &newval, sizeof(int));
    newval = 6;
    append(&root, &newval, sizeof(int));
    newval = 7;
    append(&root, &newval, sizeof(int));
    newval = 8;
    append(&root, &newval, sizeof(int));

    traversal_func(root);

    newval = 9;
    unshift(&root, &newval, sizeof(int));

    traversal_func(root);

    invert_list(&root);

    traversal_func(root);

    last_popped = pop(&root);
    printf("last popped is ");
    print_node_value(last_popped);
    printf("\n");
    free(last_popped);

    invert_list(&root);

    traversal_func(root);

    last_popped = pop(&root);
    printf("last popped is ");
    print_node_value(last_popped);
    printf("\n");
    free(last_popped);


    invert_list(&root);

    traversal_func(root);
    last_popped = pop(&root);
    printf("last popped is ");
    print_node_value(last_popped);traversal_func(root);
    traversal_func(root);

    last_popped = pop(&root);
    printf("last popped is ");
    print_node_value(last_popped);
    printf("\n");
    free(last_popped);


    invert_list(&root);

    traversal_func(root);

    float fnewval = 32.5;
    append(&root, &fnewval, TYPE_FLOAT);

    fnewval = 51.3;
    append(&root, &fnewval, TYPE_FLOAT);

    char cnewval = 'c';
    append(&root, &cnewval, TYPE_CHAR);

    traversal_func(root);

    last_popped = pop(&root);
    printf("last popped is ");
    print_node_value(last_popped);
    printf("\n");
    free(last_popped);

    last_popped = pop(&root);
    printf("last popped is ");
    print_node_value(last_popped);
    printf("\n");
    free(last_popped);

    last_popped = pop(&root);
    printf("last popped is ");
    print_node_value(last_popped);
    printf("\n");
    free(last_popped);

    traversal_func(root);

    printf("this is doone");
}