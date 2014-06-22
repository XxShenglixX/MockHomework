#include "Storage.h"
#include "ErrorCode.h"
#include "CException.h"
#include <stdio.h>


/**
 * Store an integer to the list
 *
 * Input:
 *	*list contains the address of the list
 *	values[] contains the array of integers to be added into the list
 *	length is the length of the list
 * 
 * If list is full, will throw ERR_LIST_FULL
 */
void store(List *list, int values[], int length)
{
	int i ;
	for ( i = 0 ; i < length ; i ++ )
		{
			if (!listIsFull(list))
				listAdd(list,values[i]) ;
			else 
				Throw(ERR_LIST_FULL);
		}
}

/**
 * Retrieve integer stored in the list 
 *
 * Input:
 *	*list contains the address of the list
 * 	*size contain the address of the storedIntegerSize
 *	
 * Output:
 *	return the starting address of the list
 *
 * If list is empty, will throw ERR_LIST_EMPTY
 */
int *retrieve(List *list,int *size)
{
	int *array ;
	int *read;
	int count = 0;
	
	array = list->buffer;
	read = list->buffer ;

	
	
	if (listIsEmpty(list))
		Throw(ERR_LIST_EMPTY);
	
	while (!listIsEmpty(list))
	{ 		
		*read= listRemove(list);
		read ++;	
		count++ ;
	}
	
	*size = count ;
	
	return array;
}