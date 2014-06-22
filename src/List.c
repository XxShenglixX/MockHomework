#include "List.h"
#include "ErrorCode.h"
#include "CException.h"
#include <stdio.h>
#include <malloc.h>

/**
 * Create a list of specific buffer length
 *
 * Input:
 *	length is the length of the stack
 */
List *listNew(int length)
{
	List *list;
	int *buffer;
	list = malloc(sizeof(List));
	buffer = malloc(sizeof(int) * length);
	list->buffer=buffer;
	list->length = length;
	list->size = 0;
}


/**
 * Delete the list object
 *
 * Input:
 *	list is the list object to delete
 */
void listDel(List *list)
{
	if (list != NULL)
	{
		free(list->buffer);
		free(list);
	}
}


/**
 * Add the integer passed in into the list
 *
 * Input:
 *	list is the list going to be added with integers
 *	data contain the integer to be added
 *
 * If list is full , will throw ERR_LIST_FULL
 */
void listAdd(List *list,int data)
{
	int *temp ; // pointer to be use for writing
	
	if(!(listIsFull(list)))
	{
		temp = ((list->buffer) + (list->size));
		*temp = data ;
		list->size++ ;
	}
	else 
		Throw(ERR_LIST_FULL);
		
}

/**
 * Remove integer stored in the list
 *
 * Input:
 *	list is the list going to be added with integers
 *	
 * Output:
 *	return the first integer stored in the list
 *
 *  If list is empty , will throw ERR_LIST_EMPTY
 */
int listRemove(List *list)
{
	int data ; // integers stored to be return
	
	if(!listIsEmpty(list))
	{
		printf ("Buffer %d : %d\n",list->buffer,*(list->buffer));
		data = *(list->buffer) ;
		list->buffer++;
		list->size -- ;
	}
	else 
		Throw(ERR_LIST_EMPTY);
		
	return data ;	
}
/** Check if list is empty 
 *
 * Input:
 *	list is the list that is going to be checked
 *
 * Output:
 *	1 if list is empty , 0 if list is not empty
 */
int listIsEmpty(List *list)
{
	if (list->size <= 0)
		return 1 ;
		
	else 
		return 0 ;
}

/** Check if list is full
 *
 * Input:
 *	list is the list that is going to be checked
 *
 * Output:
 *	1 if list is full , 0 if list is not full
 */
int listIsFull(List *list)
{
	if (list->size >= list->length)
		return 1 ;
		
	else 
		return 0 ;
}