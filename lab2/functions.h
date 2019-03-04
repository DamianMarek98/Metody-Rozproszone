#ifndef __LINUX_FILW_H
#define __LINUX_FILE_H

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
    struct element *head;
};

void push_back(struct list *list, int val);

void pop(struct list *list);

void print(struct list *list, int a);

void insert(struct list *list, int val, int posNew);

void removeA(struct list *list, int pos);

#endif
