#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct element
{
	struct element *previous;
	int number;
	struct element *next;
};
struct list {
	element *head;
};

//push to the end of the list
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
//delete last elementy of the list
void pop(struct list *list) {
	struct element *p;
	p = list->head;
	if (list->head == NULL) {//check if list is empty
		printf("Empty List\n");
	}
	else if (p->next==NULL && p->previous==NULL) {//if only one element exists in the list
		free(p);
		list->head->number = NULL;
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

void print(struct list *list, bool backwards = false) {
	struct element *p;
	p = list->head;
	if (list->head== NULL) {
		printf("Empty List\n");
	}
	else {
		if (backwards) {
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
			push_back(list, val);
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
			pop(list);
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




int main()
{
	//dzia³a
	struct list base;
	struct list *list = &base;
	list->head = NULL;
	push_back(list, 5);
	push_back(list, 4);
	insert(list, 6, 1);
	print(list);
	print(list, true);


	int value;
	int pos;
	bool what = false;
	char key;
	while (true)
	{
		printf("Type sign of operation You want to do (1-pushback 2-popback 3-print 4-insert 5-remove):\n");
		scanf_s("%c", &key);
		getchar();
		switch (key)
		{
		case '1':
			printf("write value:\n");
			scanf_s("%d", &value);
			getchar();
			push_back(list, value);
			break;
		case '2':
			pop(list);
			break;
		case '3':
			printf("type 1 to backward:\n");
			scanf_s("%c", &key);
			getchar();
			if (key == '1') {
				print(list, true);
			}
			else {
				print(list);
			}
			break;
		case '4':
			printf("write value and press enter:\n");
			scanf_s("%d", &value);
			getchar();
			printf("write pos and press enter:\n");
			scanf_s("%d", &pos);
			getchar();
			insert(list, value, pos-1);
			break;
		case '5':
			printf("write pos and press enter:\n");
			scanf_s("%d", &pos);
			getchar();
			removeA(list, pos);
			break;
		default:
			printf("bad input\n");
			getchar();
		}
	}


	return 0;
}