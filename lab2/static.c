#include "functions.h"


void insert(struct list *list, int val, int posNew) {
	struct element *p;
	p = list->head;
	if (list->head == NULL && posNew == 0) {
		struct element* newhead = (struct element *) malloc(sizeof(struct element));
		p->next = newhead;
		newhead->next = NULL;
		newhead->number = val;
		newhead->previous = NULL;
	}
	else if (list->head == NULL) {
		printf("Empty list\n");
	}
	else {
		bool canadd = true;
		for (int i = 0; i < posNew - 1; i++) {
			if (p->next == NULL) {//null
				printf("Too far\n");
				canadd = false;
				i = posNew;
			}
			p = p->next;
		}
		if (canadd == true && p->next == NULL) { //if the element we want to add will be the last one
			//push_back(list, val);
		}
		else if (canadd == true) {
			struct element* next;
			next = p->next;
			struct element* newEl = (struct element *) malloc(sizeof(struct element));
			newEl->next = next;
			newEl->previous = p;
			newEl->number = val;
			p->next = newEl;
			next->previous = newEl;
			printf("Succesfully added!\n");
		}
	}
}

void removeA(struct list *list, int pos) {
	struct element *p;
	p = list->head;
	if (list->head == NULL) {
		printf("Empty List\n");
	}
	else {
		bool canrem = true;
		for (int i = 0; i < pos-1; i++) {
			if (p->next == NULL) {
				printf("Too far\n");
				canrem = false;
				i = pos;
			}
			p = p->next;
		}
		if (canrem == true && p->next == NULL) { //if the element we want to add will be the alt one
			//pop(list);
		}
		else if(canrem==true) {
			struct element* prev;
			struct element* next;
			prev = p->previous;
			next = p->next;
			prev->next = next;
			next->previous = prev;
			printf("Succesfully removed!\n");
			free(p);
		}
	}
}
