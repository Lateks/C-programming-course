/* Exercises 5 and 6: a singly linked list. */
#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    struct list_node* first_node;
} List;

typedef struct list_node {
    int value;
    struct list_node* next;
} Node;

/* Return a node bearing the given integer value. */
Node *make_node(int value) {
    Node* new_node = malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

/* Insert a new node after the given node. */
void insert_after(Node *node, Node *new_node) {
    new_node->next = node->next;
    node->next = new_node;
}

/* Insert a node at the beginning of a list. */
void insert_at_beginning(List *list, Node *new_node) {
    new_node->next = list->first_node;
    list->first_node = new_node;
}

/* Remove the node that follows the given node. */
void remove_after(Node *node) {
    Node* old = node->next;
    node->next = node->next->next;
    free(old);
}

/* Remove the node at the beginning of the given list. */
void remove_at_beginning(List *list) {
    Node* old = list->first_node;
    list->first_node = list->first_node->next;
    free(old);
}

/* Print out a list */
void print_list(List* list) {
    Node* current = list->first_node;
    while (current) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void destroy_list(List *list) {
    Node* current = list->first_node;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

int main(void) {
    List* list = malloc(sizeof(List));
    Node* first = make_node(1);
    list->first_node = first;
    print_list(list);

    Node* node1 = make_node(0);
    Node* node2 = make_node(2);

    insert_at_beginning(list, node1);
    print_list(list);

    insert_after(first, node2);
    print_list(list);

    remove_after(node1);
    print_list(list);

    remove_at_beginning(list);
    print_list(list);

    destroy_list(list);

    return 0;
}
