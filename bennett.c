//
// Created by Bennett Joyce on 2/20/20.
//

//
// Created by Sykes, David A on 2/16/20.
//

#include <stdlib.h>
#include<stdio.h>
#include "intlist.h"

#define DEBUG 1


static struct Node *locate_kth_node(const struct IntList *int_list_ptr, unsigned int k);
// Return a pointer to the node associated with index k

static struct Node *new_node(int value, struct Node *next_node_ptr);
// Return a new node allocated from the heap and initialized using
// the values of the arguments

static void print_int_list(struct IntList *int_list_ptr);
// Print the list


void init_int_list(struct IntList *int_list_ptr) {
    // Initialize the size, head node pointer, and tail node pointer.
    int_list_ptr->size = 0;
    int_list_ptr->head_node_ptr = NULL;
    int_list_ptr->tail_node_ptr = NULL;
}


void destroy_int_list(struct IntList *int_list_ptr) {
    // Free each node in the chain.
    struct Node* temp = int_list_ptr->head_node_ptr;
    while (temp->next_node_ptr != NULL) {
        int_list_ptr->head_node_ptr = NULL;
        temp = temp->next_node_ptr;
        int_list_ptr->head_node_ptr = temp;
    }
    int_list_ptr->head_node_ptr = NULL;
    int_list_ptr->tail_node_ptr = NULL;
    int_list_ptr->size = 0;

    // TODO



}


void append_int_list(struct IntList *int_list_ptr, int value) {
    // value off by 1. fresh_node->value is not updated.


    // Add a new node to the end of the chain, updating the tail node ptr.
    if (int_list_ptr->head_node_ptr == NULL) {
        printf("%s%d\n", "value: ", value );
        // Appending to an empty list, a special case because the last
        // node also becomes the first node.
        struct Node *head = NULL;
        head = new_node(value, head);
        int_list_ptr->head_node_ptr = head;
        printf("%s%d\n", "ptr value: ", int_list_ptr->head_node_ptr->value);
        int_list_ptr->tail_node_ptr = int_list_ptr->head_node_ptr;
    }
    else {
        // Appending to a non-empty list.
        struct Node* node = NULL;
        node = new_node(value, node);
        int_list_ptr->tail_node_ptr->next_node_ptr = node;
        int_list_ptr->tail_node_ptr = int_list_ptr->tail_node_ptr->next_node_ptr;
    }
    ++int_list_ptr->size;
    // TODO
}


int get_int_list_item_at(const struct IntList *int_list_ptr, unsigned int index) {
    // Return the int value stored in the node associated with the index value.
    return locate_kth_node(int_list_ptr, index)->value;
}


void set_int_list_item_at(struct IntList *int_list_ptr, unsigned int index, int value) {
    // Set the value stored in the node associated with the index value to a new value.
    locate_kth_node(int_list_ptr, index)->value = value;
}


void remove_list_item_at(struct IntList *int_list_ptr, unsigned int index) {

    if (DEBUG) {
        printf("Before removing the item at index %u:\n", index);
        print_int_list(int_list_ptr);
    }
    if (index == 0) {
        // Removing the first node
        struct Node *first_node_ptr = int_list_ptr->head_node_ptr;
        int_list_ptr->head_node_ptr = first_node_ptr->next_node_ptr;
        int_list_ptr->tail_node_ptr = first_node_ptr->next_node_ptr;
        free(first_node_ptr);
    }
    else {
        ++int_list_ptr->size;
    }
    --int_list_ptr->size;
}


void insert_int_list_item_at(struct IntList *int_list_ptr, unsigned int index, int value) {
    if (index == int_list_ptr->size) {
        append_int_list(int_list_ptr, value);
    }
    else if (index == 0) {
        // insert at the front
        struct Node *node_ptr = new_node(value, int_list_ptr->head_node_ptr);
        int_list_ptr->head_node_ptr = node_ptr;
    }
    else {
        struct Node* temp = new_node(value, locate_kth_node(int_list_ptr, index));
        temp->next_node_ptr = locate_kth_node(int_list_ptr, index);
        locate_kth_node(int_list_ptr, index - 1)->next_node_ptr = temp;
    }
    ++int_list_ptr->size;
    // TODO
}


unsigned int int_list_size(const struct IntList *int_list_ptr) {
    return int_list_ptr->size;
}


struct Node *locate_kth_node(const struct IntList *int_list_ptr, unsigned int k) {
    struct Node * node_ptr = int_list_ptr->head_node_ptr;
    for (unsigned int i = 0; i < k; i++) {
        node_ptr = node_ptr->next_node_ptr;
    }
    if(node_ptr != NULL) {
        return node_ptr;
    } else {

    }

    // TODO
}


static struct Node *new_node(int value, struct Node *next_node_ptr) {
    // Get a new node from the heap and set its value and next node pointer.
    struct Node *node_ptr = (struct Node *)malloc(sizeof(struct Node));
    node_ptr->value = value;
    // ????? Not sure on this one
    // TODO
    node_ptr->next_node_ptr = next_node_ptr;
    return node_ptr;

    // TODO
}


static void print_int_list(struct IntList *int_list_ptr) {
    printf("HERE");
    printf("IntList{size: %u, head_node_ptr: %p, tail_node_ptr: %p}\n", int_list_ptr->size,
           int_list_ptr->head_node_ptr, int_list_ptr->tail_node_ptr);
    for (struct Node *p = int_list_ptr->head_node_ptr; p ; p = p->next_node_ptr) {
        printf("   %p {value: %d, next_node_ptr: %p}\n", p, p->value, p->next_node_ptr);
    }
}
