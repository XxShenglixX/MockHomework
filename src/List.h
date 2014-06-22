#ifndef List_H
#define List_H

typedef struct 
{
	int *buffer;
	int size ;
	int length;
}List ;

List *listNew(int length);
void listDel(List *list);
void listAdd(List *list,int data);
int listRemove(List *list);
int listIsEmpty(List *list);
int listIsFull(List *list);

#endif // List_H
