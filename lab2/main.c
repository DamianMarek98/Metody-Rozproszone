#include "functions.h"

int main()
{
	struct list base;
	struct list *list = &base;
	list->head = NULL;


	int value;
	int pos;
	int what=0;
	char key=3;
	while (true)
	{
		printf("Type sign of operation You want to do (1-pushback 2-popback 3-print 4-insert 5-remove):\n");
		scanf(&key);
	key='3';
		switch (key)
		{
		case '1':
			printf("write value:\n");
			
			getchar();
			push_back(list, value);
			break;
		case '2':
			pop(list);
			break;
		case '3':
			printf("type 1 to backward:\n");
			
			getchar();
			print(list,key);
			break;
		
		default:
			printf("bad input\n");
			getchar();
		}
	}


	return 0;
}
