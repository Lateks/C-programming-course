/* Exercises 7 to 9: a doubly linked list. */
#include <stdio.h>

typedef struct list_node {
    int value;
    struct list_node* prev;
    struct list_node* next;
} Node;

typedef struct list {
    Node* first_node;
    Node* last_node;
} List;

/* Node constructor. */
Node make_node(int value) {
    Node new_node;
    new_node.value = value;
    new_node.prev = NULL;
    new_node.next = NULL;
    return new_node;
}

/* Inserts the new node after the given existing node. */
void insert_after(Node *node, Node *new_node) {
    new_node->prev = node;
    new_node->next = node->next;
    node->next = new_node;
}

/* Inserts the new node in the beginning of the given list. */
void insert_at_beginning(List *list, Node *new_node) {
    list->first_node->prev = new_node;
    new_node->next = list->first_node;
    list->first_node = new_node;
}

/* Removes the given node. */
void remove_from_list(List *list, Node *node) {
    if (node->prev)
        node->prev->next = node->next;
    else
        list->first_node = node->next;
    if (node->next)
        node->next->prev = node->prev;
    else
        list->last_node = node->prev;
}

/* Print out a list */
void print_list(List *list) {
    Node *current = list->first_node;
    while (current) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    List list;
    Node first = make_node(1);
    list.first_node = list.last_node = &first;
    print_list(&list);

    Node node1 = make_node(0);
    Node node2 = make_node(2);

    insert_at_beginning(&list, &node1);
    print_list(&list);

    insert_after(&first, &node2);
    print_list(&list);

    remove_from_list(&list, &node1);
    print_list(&list);

    remove_from_list(&list, &node2);
    print_list(&list);

    return 0;
}
