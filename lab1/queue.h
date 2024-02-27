//
// Created by jerzy on 27.02.24.
//

#ifndef QUEUE_H
#define QUEUE_H

#endif //QUEUE_H

typedef struct queue queue;
struct queue {
    void *data;
    queue *next;
    queue *prev;
};

void qinsert(queue** head, void *data);

void qlist(queue *head, void (*print_data)(void *));

void qpop(queue **head);

void qswap(queue **head, int index1, int index2);


