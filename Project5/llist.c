#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

// Function to allocate a new node with a given value
struct node *node_alloc(int value) {
    struct node *n = malloc(sizeof(struct node));
    if (!n) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    n->value = value;
    n->next = NULL;
    return n;
}

// Function to free a single node
void node_free(struct node *n) {
    free(n);
}

// Function to insert a node at the head of the list
void llist_insert_head(struct node **head, struct node *n) {
    n->next = *head;
    *head = n;
}

// Function to delete and return the node at the head of the list
struct node *llist_delete_head(struct node **head) {
    if (*head == NULL) return NULL;
    struct node *removed_node = *head;
    *head = (*head)->next;
    removed_node->next = NULL;
    return removed_node;
}

// Function to insert a node at the tail of the list
void llist_insert_tail(struct node **head, struct node *n) {
    if (*head == NULL) {
        *head = n;
        return;
    }

    struct node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = n;
}

// Print the linked list
void llist_print(struct node *head) {
    if (head == NULL) {
        printf("[empty]\n");
        return;
    }

    struct node *current = head;
    while (current != NULL) {
        printf("%d", current->value);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

// free the entire list
void llist_free(struct node **head) {
    struct node *current = *head;
    while (current != NULL) {
        struct node *next_node = current->next;
        node_free(current);
        current = next_node;
    }
    *head = NULL;
}

// Main function to parse command line arguments
int main(int argc, char *argv[]) {
    struct node *head = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "ih") == 0 && i + 1 < argc) {
            int value = atoi(argv[++i]);
            struct node *new_node = node_alloc(value);
            llist_insert_head(&head, new_node);
        } 
        else if (strcmp(argv[i], "it") == 0 && i + 1 < argc) {
            int value = atoi(argv[++i]);
            struct node *new_node = node_alloc(value);
            llist_insert_tail(&head, new_node);
        } 
        else if (strcmp(argv[i], "dh") == 0) {
            struct node *removed_node = llist_delete_head(&head);
            if (removed_node) {
                node_free(removed_node);
            }
        } 
        else if (strcmp(argv[i], "f") == 0) {
            llist_free(&head);
        } 
        else if (strcmp(argv[i], "p") == 0) {
            llist_print(head);
        }
    }

    return 0;
}
