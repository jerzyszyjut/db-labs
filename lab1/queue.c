//
// Created by jerzy on 27.02.24.
//

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

void
qlist(queue *head, void (*print_data)(void *)) {
    queue *p = head;

    while (p != NULL) {
        print_data(p->data);
        printf("\n");
        p = p->next;
    }
}

void
qinsert(queue **head, void *data) {
    queue* current_node = *head;

    if(current_node == NULL)
    {
        queue* new_node = (queue*)malloc(sizeof(queue));
        new_node->data = data;
        new_node->next = NULL;
        new_node->prev = NULL;
        *head = new_node;
        return;
    }

    while (current_node->next != NULL)
    {
        current_node = current_node->next;
    }

    queue* new_node = (queue*)malloc(sizeof(queue));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = current_node;
    current_node->next = new_node;
}


void qpop(queue **head) {
    if(*head == NULL) return;

    queue* second_node = (*head)->next;
    free(*head);
    *head = second_node;
    second_node->prev = NULL;
}

void qswap(queue **head, int index1, int index2) {
    if(*head == NULL) return;

    int index = 0;
    queue* node1 = NULL;
    queue* node2 = NULL;
    queue* current_node = *head;

    while ((index1 <= index || index2 <= index) && current_node != NULL) {
        if(index == index1) {
            node1 = current_node;
        }
        if(index == index2) {
            node2 = current_node;
        }
        current_node = current_node->next;
        index++;
    }

    if(node1 == NULL || node2 == NULL) {
        return;
    }

    if(node1->prev != NULL) {
        node1->prev->next = node2;
    }

    if(node1->next != NULL) {
        node1->next->prev = node2;
    }

    if(node2->prev != NULL) {
        node2->prev->next = node1;
    }

    if(node2->next != NULL) {
        node2->next->prev = node1;
    }

    queue* temp_node_1_prev = node1->prev, *temp_node_1_next = node1->next;

    node1->prev = node2->prev;
    node1->next = node2->next;
    node2->prev = temp_node_1_prev;
    node2->next = temp_node_1_next;

    if(index1 == 0) {
        *head = node2;
    }

    if(index2 == 0) {
        *head = node1;
    }
}
