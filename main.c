//
// Created by Sykes, David A on 2/16/20.
//

#include <stdio.h>
#include <form.h>

#include "intlist.h"

void check_list(const char *message, struct IntList *int_list_ptr, int *a, int n);
// Check that the values in int_list match up with the
// n values in array a

void check_empty(const char *message, struct IntList *int_list_ptr);
    // Verify that a list is empty

void print_list(struct IntList *int_list_ptr);

int main(int argc, const char * argv[]) {

    struct IntList my_int_list ;//= {100, NULL, NULL};
    int items[10] = {5, 10, 15, 20, 25, 30, 40, 50, 60, 70};
    int n = 5;
    int i;

    init_int_list(&my_int_list);
    check_empty("After initializing my_int_list", &my_int_list);

    // Append some values to the list
    printf("1. Append items\n");
    for (i = 0; i < n; ++i) {
        printf("    append_int_list(%p, %d)\n", &my_int_list, items[i]);
        append_int_list(&my_int_list, items[i]);

        printf("        size is now %u\n", int_list_size(&my_int_list));
    }
    check_list("After appending", &my_int_list, items, n);
    print_list(&my_int_list);

    printf("2. Set items to new values by adding 1 to each\n");
    // Set each value in the list to a new value
    for (i = 0; i < n; ++i) {
        items[i] += 1;
        printf("    .set_int_list_item_at(%p, %d, %d)\n", &my_int_list, i, items[i]);
        set_int_list_item_at(&my_int_list, i, items[i]);
    }
    check_list("After adding 1 to each list item", &my_int_list, items, n);
    print_list(&my_int_list);

    printf("3. Insert items\n");
    int items2[] = {1, 6, 11, 13, 16, 21, 26, 31};
    printf("    insert_int_list_item_at(%p, 0, 1)\n", &my_int_list);
    insert_int_list_item_at(&my_int_list, 0, 1);
    printf("    insert_int_list_item_at(%p, 3, 13)\n", &my_int_list);
    insert_int_list_item_at(&my_int_list, 3, 13);
    printf("    insert_int_list_item_at(%p, 7, 31)\n", &my_int_list);
    insert_int_list_item_at(&my_int_list, 7, 31);
    check_list("After inserting items", &my_int_list, items2, 8);
    print_list(&my_int_list);

    // Insert items into an empty list
    struct IntList int_list3;
    int items3[] = {100, 200};
    init_int_list(&int_list3);
    printf("Inserting 100 into an empty list at index position 0.\n");
    insert_int_list_item_at(&int_list3, 0, 100);
    check_list("After inserting into an empty list", &int_list3, items3, 1);
    printf("    Appending 200 to that list.\n");
    append_int_list(&int_list3, 200);
    check_list("After appending 200", &int_list3, items3, 2);
    print_list(&int_list3);

    printf("4. Remove items\n");
    // Remove the first item, the last item, and then the others "at random"
    // items2 contains a copy of the items in my_int_list
    unsigned int index_to_remove[] = {0, 6, 2, 2, 3, 1, 0, 0};
    int states[8][8] = { {6, 11, 13, 16, 21, 26, 31},
                         {6, 11, 13, 16, 21, 26},
                         {6, 11, 16, 21, 26},
                         {6, 11, 21, 26},
                         {6, 11, 21,},
                         {6, 21},
                         {21},
                         {} };
    const unsigned int N = sizeof(index_to_remove) / sizeof(unsigned int);
    for (int i = 0; i < N; ++i) {
        unsigned int k = index_to_remove[i];
        printf("    remove_int_list_at(%p, %u)\n", &my_int_list, k);
        remove_list_item_at(&my_int_list, k);
        check_list("After removing an item", &my_int_list, &(states[i][0]), N - i - 1);
        print_list(&my_int_list);
    }

    printf("destroy_int_list(%p)\n", &my_int_list);
    destroy_int_list(&my_int_list);
    check_empty("After destroying my_int_list", &my_int_list);

    printf("destroy_int_list(%p)\n", &int_list3);
    destroy_int_list(&int_list3);
    check_empty("After destroying int_list3", &my_int_list);

    return 0;
}



void print_list(struct IntList *int_list_ptr) {
    printf("Here is the list: [");
    for (int i = 0; i < int_list_size(int_list_ptr); ++i) {
        printf(" %d", get_int_list_item_at(int_list_ptr, i));
    }
    printf(" ]\n");
}

void check_list(const char *message, struct IntList *int_list_ptr, int *a, int n) {
    const int *q = a + n;
    int *p = a;
    struct Node *node_ptr;

    printf("\n\nCHECKING %s:\n    Expected    Actual\n    --------    ------\n", message);
    for (p = a, node_ptr = int_list_ptr->head_node_ptr; p != q && node_ptr ; ++p, node_ptr = node_ptr->next_node_ptr) {
        if  (*p == node_ptr->value) {
            printf("    %8d    %6d\n", *p, node_ptr->value);
        }
        else {
            printf("    %8d <> %6d\n", *p, node_ptr->value);
        }
    }
    if (p != q) {
        printf("    MORE VALUES EXPECTED.\n");
    }
    else if (node_ptr) {
        printf("    THE LIST CONTAINS MORE VALUES THAN EXPECTED\n");
    }
    else {
        printf("    --------    ------\n");
    }
}

void check_empty(const char *message, struct IntList *int_list_ptr) {
    if (int_list_ptr->size == 0 && int_list_ptr->head_node_ptr == NULL && int_list_ptr->tail_node_ptr == NULL) {
        printf("    This empty list is has the correct structure: ");
    }
    else {
        printf("    This empty list is has an INCORRECT structure: ");
    }
    printf("{size: %u, head_node_ptr: %p, tail_node_ptr: %p}\n", int_list_ptr->size,
            int_list_ptr->head_node_ptr, int_list_ptr->tail_node_ptr);
}
