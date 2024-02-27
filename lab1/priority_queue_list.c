#include <stdio.h>
#include <stdlib.h>
#include "priority_queue_list.h"

void
qlist(pqueue *head, void (*print_data)(void *)) {
	pqueue *p;
	
	for (p = head; p != NULL; p = p->next) {
		printf("%d: ", p->k);
		print_data(p->data);
		printf("\n");
	}
	
}

void
qinsert(pqueue **phead, void *data, int k) {
	pqueue* current_node = *phead;

	if(current_node == NULL)
	{
		pqueue* new_node = (pqueue*)malloc(sizeof(pqueue));
		new_node->k = k;
		new_node->data = data;
		new_node->next = NULL;
		new_node->prev = NULL;
		*phead = new_node;
		return;
	}

	while (current_node != NULL)
	{
		if (current_node->k > k) {
			pqueue* new_node = (pqueue*)malloc(sizeof(pqueue));
			new_node->k = k;
			new_node->data = data;
			new_node->next = current_node;
			new_node->prev = current_node->prev;
			current_node->prev = new_node;
			if (new_node->prev != NULL)
			{
				new_node->prev->next = new_node;
			}
			else
			{
				*phead = new_node;
			}
			return;
		}

		if(current_node->next == NULL) {
			pqueue* new_node = (pqueue*)malloc(sizeof(pqueue));
			new_node->k = k;
			new_node->data = data;
			new_node->next = NULL;
			new_node->prev = current_node;
			current_node->next = new_node;
			return;
		}
		current_node = current_node->next;
	}
}


void
qremove(pqueue **phead, int k) {
	pqueue* current_node = *phead;

	while (current_node != NULL)
	{
		if (current_node->k == k)
		{
			if (current_node->prev != NULL)
			{
				current_node->prev->next = current_node->next;
			}
			else
			{
				*phead = current_node->next;
			}
			if (current_node->next != NULL)
			{
				current_node->next->prev = current_node->prev;
			}
			free(current_node);
			return;
		}
		current_node = current_node->next;
	}
}

