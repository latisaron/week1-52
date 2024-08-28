#include <stdio.h>
#include <stdlib.h>

struct LinkedList {
    int value;
    struct LinkedList* next;
    void (*traversal_func)(struct LinkedList*);
    int (*pop)(struct LinkedList*);
    void (*unshift)(struct LinkedList**, int); 
    void (*append)(struct LinkedList*, int); 
};

void traversal_func(struct LinkedList* obj);
int pop(struct LinkedList* obj);
void unshift(struct LinkedList** head_ref, int value);
void append(struct LinkedList* obj, int value);

void traversal_func(struct LinkedList* obj) {
    struct LinkedList* cur = obj;
    while (cur->next != NULL) {
        printf("obj value is %d \n", cur->value);
        cur = cur->next;
    }
    printf("obj value is %d \n", cur->value);
    printf("---------------\n");
};

int pop(struct LinkedList* obj) {
    struct LinkedList* cur = obj;
    struct LinkedList* prev = obj;
    while (cur->next != NULL) {
        prev = cur;
        cur = cur->next;
    }
    prev->next = NULL;

    int final_value = cur->value;
    free(cur);
    return final_value;
};

void unshift(struct LinkedList** obj, int value) {
    struct LinkedList* new_node = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    new_node->value = value;
    new_node->next = *obj;
    new_node->traversal_func = traversal_func;
    new_node->pop = pop;
    new_node->unshift = unshift;
    new_node->append = append;
    *obj = new_node;
    return;
};

void append(struct LinkedList* obj, int value) {
    struct LinkedList* cur = obj;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    struct LinkedList* empty_pointer = NULL;
    struct LinkedList* new_node = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    new_node->value = value;
    new_node->next = empty_pointer;
    new_node->traversal_func = traversal_func;
    new_node->pop = pop;
    new_node->unshift = unshift;
    new_node->append = append;
    
    cur->next = new_node;
    return;
};

void main() {
    struct LinkedList* empty_pointer = NULL;

    struct LinkedList* aron = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    struct LinkedList* clau = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    struct LinkedList* ener = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    struct LinkedList* root = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    
    aron->value = 4;
    aron->next= empty_pointer;
    aron->traversal_func = traversal_func;
    aron->pop = pop;
    aron->unshift = unshift;
    aron->append = append;
        
    clau->value = 3;
    clau->next= aron;
    clau->traversal_func = traversal_func;
    clau->pop = pop;
    clau->unshift = unshift;
    clau->append = append;
        
    ener->value = 2;
    ener->next= clau;
    ener->traversal_func = traversal_func;
    ener->pop = pop;
    ener->unshift = unshift;
    ener->append = append;
        
    root->value = 1;
    root->next= ener;
    root->traversal_func = traversal_func;
    root->pop = pop;
    root->unshift = unshift;
    root->append = append;
        

    root->traversal_func(root);
    int last_popped;
    
    last_popped = root->pop(root);
    printf("last popped is %d\n", last_popped);

    last_popped = root->pop(root);
    printf("last popped is %d\n", last_popped);

    last_popped = root->pop(root);
    printf("last popped is %d\n", last_popped);

    // last_popped = root->pop(&root);
    // printf("last popped is %d\n", last_popped);

    root->traversal_func(root);
    
    root->append(root, 5);
    root->append(root, 6);
    root->append(root, 7);
    root->append(root, 8);

    root->traversal_func(root);

    root->unshift(&root, 9);

    root->traversal_func(root);

    printf("aron heii");
}