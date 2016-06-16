#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "linklist.h"

void assertlist(struct list_node *list) {
    if(list == NULL) {
        fprintf(stderr, "NULL list assertion");
        exit(-1);
    }
}

struct list_node * node_at_index(struct list_node *list, uint32_t i) {
    uint32_t index = i;//Extra copy for error message
    struct list_node *current = list;
    while((i--) > 0) {
        if(current->next == NULL) {
            fprintf(stderr, "Index %d out of bounds, length %d", index, list_len(list));
            exit(-1);
        }
        current = current->next;
    }
    return current;
}

lnk_list * list_create(void *data) {
    struct list_node *list = malloc(sizeof(struct list_node));
    list->data = data;
    list->next = NULL;
    return list;
}

uint32_t list_len(struct list_node *list) {
    uint32_t len = 0;
    struct list_node *current = list;
    while(current != NULL) {
        len++;
        current = current->next;
    }
    return len;
}

void list_append(struct list_node *list, void *data) {
    assertlist(list);
    struct list_node *current = list;
    while(1) {
        if(current->next == NULL) {
            struct list_node *new = list_create(data);
            current->next = new;
            return;
        }
        else {
            current = current->next;
        }
    }
}

void list_free(struct list_node *list) {
    assertlist(list);
    struct list_node *current = list;
    while(1) {
        if(current == NULL) {
            return;
        }
        struct list_node *next = current->next;
        free(current);
        current = next;
    }
}

void * list_get(struct list_node *list, uint32_t i) {
    assertlist(list);
    return node_at_index(list, i)->data;
}

void list_set(struct list_node *list, uint32_t i, void *data) {
    assertlist(list);
    node_at_index(list, i)->data = data;
}

void list_itterate(struct list_node *list, void (*func)(void*)) {
    assertlist(list);
    struct list_node *current = list;
    while(current != NULL) {
        func(current->data);
        current = current->next;
    }
}
