#include "functions.h"

void pop(struct list *list) {
	struct element *p;
	p = list->head;
	if (list->head == NULL) {//check if list is empty
		printf("Empty List\n");
	}
	else if (p->next==NULL && p->previous==NULL) {//if only one element exists in the list
		free(p);
		//list->head->number = NULL;
		list->head->next = NULL;
		list->head->previous = NULL;
		list->head = NULL;
		printf("Empty List\n");
	}
	else {
		while (p->next != NULL) {//move last element to p
			p = p->next;
		}
		if (p->previous != NULL) {
			struct element* prev;
			prev = p->previous;
			prev->next = NULL;
		}
		printf("Succesfully removed!\n");
		free(p);
	}
}

void push_back(struct list *list, int val) {
	struct element *p;
	p = list->head;
	if (list->head== NULL) {//if list is empty
		struct element* newhead = (struct element *) malloc(sizeof(struct element));
		list->head = newhead;
		list->head->next = NULL;
		list->head->number = val;
		list->head->previous = NULL;
	}
	else {//not empty
		while (p->next != NULL) {
			p = p->next;
		}
		struct element* newEl = (struct element *) malloc(sizeof(struct element));
		p->next = newEl;
		newEl->next = NULL;
		newEl->number = val;
		newEl->previous = p;
	}
	printf("Succesfully added!\n");
}

void print(struct list *list, int a) {
    printf("czescha\n");
	struct element *p;
	p = list->head;
	if (list->head== NULL) {
		printf("Empty List\n");
	}
	else {
		if (a==1) {
			while (p->next != NULL) {
				p = p->next;
			}
			printf("%d ", p->number);
			while (p->previous != NULL) {
				p = p->previous;
				printf("%d ", p->number);
			}
		}
		else {
			printf("%d ", p->number);
			while (p->next != NULL) {
				p = p->next;
				printf("%d ", p->number);
			}
		}
	}
	printf("\n");
}
