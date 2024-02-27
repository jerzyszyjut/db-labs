#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

typedef struct process process;
struct process {
	char name[40];
};

void
print_process(void *data) {
	process *pr = (process *)data;
	printf("%s", pr->name);
}

int
main(int argc, char **argv) {
	
	queue *q = NULL;
	process *p1, *p2, *p3;
	p1 = (process *) malloc(sizeof(process));
	strcpy(p1->name, "Firefox");
	p2 = (process *) malloc(sizeof(process));
	strcpy(p2->name, "Geany IDE");
	p3 = (process *) malloc(sizeof(process));
	strcpy(p3->name, "Important Calculations");

	qinsert(&q, p1);
	qinsert(&q, p2);
	qinsert(&q, p3);
	qlist(q, print_process);
	printf("\n");

	qswap(&q, 0, 2);
	qlist(q, print_process);

	printf("\n");
	qpop(&q);
	qlist(q, print_process);
	
	printf("\n");
	qinsert(&q, p2);
	qlist(q, print_process);
	
	printf("\n");
	qpop(&q);
	qlist(q, print_process);
	
	printf("\n");
	qpop(&q);
	qlist(q, print_process);
	
	free(p1);
	free(p2);
	free(p3);	
		
	return 0;
}
