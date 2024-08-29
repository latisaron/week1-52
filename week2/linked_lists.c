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