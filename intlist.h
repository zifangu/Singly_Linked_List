//
// Created by Sykes, David A on 2/16/20.
//

#ifndef SINGLYLINKEDLISTPROJECT_INTLIST_H
#define SINGLYLINKEDLISTPROJECT_INTLIST_H


// We should use a forward declaration for this type and define it in intlist.c, but for
// testing purposes it is defined here.
struct Node {
    int value;
    struct Node *next_node_ptr;
};

struct IntList {
    struct Node *head_node_ptr;
    struct Node *tail_node_ptr;
    unsigned int size;
};

void init_int_list(struct IntList *int_list_ptr);
    // Initialize a new IntList
    // Must be invoked before any other functions that operate on the structure.

void destroy_int_list(struct IntList *int_list_ptr);
    // Destroy an IntList
    // Must be called to free internally sued storage.

void append_int_list(struct IntList *int_list_ptr, int value);
    // Append a value to the end of an IntList

int get_int_list_item_at(const struct IntList *int_list_ptr, unsigned int index);
    // Get the value associated with a given index in the IntList.
    // Precondition: 0 <= index < int_list_size(int_list_ptr)

void set_int_list_item_at(struct IntList *int_list_ptr, unsigned int index, int value);
    // Replace the value associated with a given index in an IntList.
    // Precondition: 0 <= index < int_list_size(int_list_ptr)

void remove_list_item_at(struct IntList *int_list_ptr, unsigned int index);
    // Remove the value associated with a given index in the IntList.
    // Precondition: 0 <= index < int_list_size(int_list_ptr)

void insert_int_list_item_at(struct IntList *int_list_ptr, unsigned int index, int value);
    // Update the list so that the value becomes associated with index in the IntList
    // Precondition: 0 <= index <= int_list_size(int_list_ptr)

unsigned int int_list_size(const struct IntList *int_list_ptr);
    // Return the number of values in the IntList.

#endif //SINGLYLINKEDLISTPROJECT_INTLIST_H
