#include <stdio.h>
#include <stdlib.h>

struct LinkedList {
    int value;
    struct LinkedList* next;
};

void traversal_func(struct LinkedList* obj) {
    struct LinkedList* cur = obj;
    if (obj == NULL) {
        printf("bad bad cant traverse emtpy \n");
        return;
    }
    while (cur->next != NULL) {
        printf("obj value is %d \n", cur->value);
        cur = cur->next;
    }
    printf("obj value is %d \n", cur->value);
    printf("---------------\n");
};

int pop(struct LinkedList** obj) {
    if (*obj == NULL) {
        printf("cannot pop anymore, list is empty \n");
        return -1;
    }
    struct LinkedList* cur = *obj;
    struct LinkedList* prev = *obj;
    while (cur->next != NULL) {
        prev = cur;
        cur = cur->next;
    }
    prev->next = NULL;

    int final_value = cur->value;
    if (cur == *obj) {
        *obj = NULL;
    }
    free(cur);
    return final_value;
};

void unshift(struct LinkedList** obj, int value) {
    struct LinkedList* new_node = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    new_node->value = value;
    new_node->next = *obj;
    *obj = new_node;
    return;
};

void append(struct LinkedList** obj, int value) {
    struct LinkedList* cur = *obj;
    struct LinkedList* empty_pointer = NULL;
    struct LinkedList* new_node = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    new_node->value = value;
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
    
    aron->value = 4;
    aron->next= empty_pointer;
        
    clau->value = 3;
    clau->next= aron;
    
    ener->value = 2;
    ener->next= clau;

    root->value = 1;
    root->next= ener;
        

    traversal_func(root);
    int last_popped;
    
    last_popped = pop(&root);
    printf("last popped is %d\n", last_popped);

    last_popped = pop(&root);
    printf("last popped is %d\n", last_popped);

    last_popped = pop(&root);
    printf("last popped is %d\n", last_popped);

    last_popped = pop(&root);
    printf("last popped is %d\n", last_popped);

    last_popped = pop(&root);
    printf("last popped is %d\n", last_popped);

    traversal_func(root);
    
    append(&root, 5);
    append(&root, 6);
    append(&root, 7);
    append(&root, 8);

    traversal_func(root);

    unshift(&root, 9);

    traversal_func(root);

    invert_list(&root);

    traversal_func(root);

    last_popped = pop(&root);
    printf("last popped is %d\n", last_popped);

    invert_list(&root);

    traversal_func(root);

    last_popped = pop(&root);
    printf("last popped is %d\n", last_popped);

    invert_list(&root);

    traversal_func(root);

    last_popped = pop(&root);
    printf("last popped is %d\n", last_popped);

    invert_list(&root);

    traversal_func(root);

    last_popped = pop(&root);
    printf("last popped is %d\n", last_popped);

    invert_list(&root);

    traversal_func(root);


    printf("this is doone");
}

// attempt to generic-alise the list but it's reaaally bad

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// struct LinkedList {
//     void* value;
//     size_t size;
//     struct LinkedList* next;
// };

// void init_generic_linked_list_node(struct LinkedList* linked_list, void* value, size_t size) {
//     linked_list->value = malloc(size);
//     if (linked_list->value == NULL) {
//         printf("failed to allocate memory");
//         return;
//     }
//     linked_list->size = size;
//     memcpy(linked_list->value, value, size);
// }

// void traversal_func(struct LinkedList* obj) {
//     struct LinkedList* cur = obj;
//     if (obj == NULL) {
//         printf("bad bad cant traverse emtpy \n");
//         return;
//     }
//     while (cur->next != NULL) {
//         if (cur->size = sizeof(int)) {
//             printf("obj value is %d \n", *(int*)(cur->value));
//         }
//         cur = cur->next;
//     }
//     if (cur->size = sizeof(int)) {
//             printf("obj value is %d \n", *(int*)(cur->value));
//         }
//     printf("---------------\n");
// };

// void* pop(struct LinkedList** obj) {
//     if (*obj == NULL) {
//         printf("cannot pop anymore, list is empty \n");
//         return NULL;
//     }
//     struct LinkedList* cur = *obj;
//     struct LinkedList* prev = *obj;
//     while (cur->next != NULL) {
//         prev = cur;
//         cur = cur->next;
//     }
//     prev->next = NULL;


//     void* final_value = cur->value;
//     if (cur == *obj) {
//         *obj = NULL;
//     }
//     free(cur);
//     return final_value;
// };

// void unshift(struct LinkedList** obj, void* value, size_t size) {
//     struct LinkedList* new_node = (struct LinkedList*)malloc(sizeof(struct LinkedList));
//     init_generic_linked_list_node(new_node, value, size);
//     new_node->next = *obj;
//     *obj = new_node;
//     return;
// };

// void append(struct LinkedList** obj, void* value, size_t size) {
//     struct LinkedList* cur = *obj;
//     struct LinkedList* empty_pointer = NULL;
//     struct LinkedList* new_node = (struct LinkedList*)malloc(sizeof(struct LinkedList));
//     init_generic_linked_list_node(new_node, value, size);
//     new_node->next = empty_pointer;
//     if (*obj == NULL) {
//         *obj = new_node;
//     } else {
//         while (cur->next != NULL) {
//             cur = cur->next;
//         }
//         cur->next = new_node;
//     }
//     return;
// };

// void invert_list(struct LinkedList** root) {
//     struct LinkedList* prev2 = NULL;
//     struct LinkedList* prev1 = NULL;
 
//     if (root != NULL) {
//         while ((*root)->next != NULL) {
//             if (prev1 != NULL) {
//                 prev1->next = prev2;
//             }
//             prev2 = prev1;
//             prev1 = *root;
//             *root = (*root)->next;
//         }
//         if (prev1 != NULL) {
//             prev1->next = prev2;
//             (*root)->next = prev1;
//         }
//     }
//     return;
// }


// void main() {
//     struct LinkedList* empty_pointer = NULL;

//     struct LinkedList* aron = (struct LinkedList*)malloc(sizeof(struct LinkedList));
//     struct LinkedList* clau = (struct LinkedList*)malloc(sizeof(struct LinkedList));
//     struct LinkedList* ener = (struct LinkedList*)malloc(sizeof(struct LinkedList));
//     struct LinkedList* root = (struct LinkedList*)malloc(sizeof(struct LinkedList));

//     int newval = 4;

//     init_generic_linked_list_node(aron, &newval, sizeof(int));
//     aron->next= empty_pointer;
        
//     newval = 3;
//     init_generic_linked_list_node(clau, &newval, sizeof(int));
//     clau->next= aron;
    
//     newval = 2;
//     init_generic_linked_list_node(ener, &newval, sizeof(int));
//     ener->next= clau;

//     newval = 1;
//     init_generic_linked_list_node(root, &newval, sizeof(int));
//     root->next= ener;
        

//     traversal_func(root);
//     void* last_popped;
    
//     last_popped = pop(&root);
//     printf("last popped is %d\n", last_popped);

//     last_popped = pop(&root);
//     printf("last popped is %d\n", last_popped);

//     last_popped = pop(&root);
//     printf("last popped is %d\n", last_popped);

//     last_popped = pop(&root);
//     printf("last popped is %d\n", last_popped);

//     last_popped = pop(&root);
//     printf("last popped is %d\n", last_popped);

//     traversal_func(root);
    
//     newval = 5;
//     append(&root, &newval, sizeof(int));
//     newval = 6;
//     append(&root, &newval, sizeof(int));
//     newval = 7;
//     append(&root, &newval, sizeof(int));
//     newval = 8;
//     append(&root, &newval, sizeof(int));

//     traversal_func(root);

//     newval = 9;
//     unshift(&root, &newval, sizeof(int));

//     traversal_func(root);

//     invert_list(&root);

//     traversal_func(root);

//     // so this is not gonna work because i need to know the type associated with the popped node
//     // i could try to return an array with the first item eing the pointer and the second one being the type
//     // but realistically this is garbage and it's really not worth the hassle of working with everything in
//     // the heap;
//     // i'd much rather go for a shit of boilerplate than spaghetti code
//     last_popped = pop(&root);
//     printf("last popped is %d\n", last_popped);

//     invert_list(&root);

//     traversal_func(root);

//     last_popped = pop(&root);
//     printf("last popped is %d\n", last_popped);

//     invert_list(&root);

//     traversal_func(root);

//     last_popped = pop(&root);
//     printf("last popped is %d\n", last_popped);

//     invert_list(&root);

//     traversal_func(root);

//     last_popped = pop(&root);
//     printf("last popped is %d\n", last_popped);

//     invert_list(&root);

//     traversal_func(root);


//     printf("this is doone");
// }