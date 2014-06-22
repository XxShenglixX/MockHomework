#include "unity.h"
#include "List.h"
#include <malloc.h>
#include <stdio.h>
#include "CException.h"
#include "ErrorCode.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_listIsEmpty_should_return_1_for_empty_list()
{
	List *list = listNew(6);
	
	TEST_ASSERT_EQUAL(1,listIsEmpty(list));
	
	listDel(list);
}

void test_listIsEmpty_given_size_1_should_return_0_for_not_empty_list()
{
	List *list = listNew(6);
	list->size = 1;
	
	TEST_ASSERT_EQUAL(0,listIsEmpty(list));
	
	listDel(list);
}

void test_listIsFull_given_size_6_should_return_1_for_full_list()
{
	List *list = listNew(6);
	list->size = 6;
	
	TEST_ASSERT_EQUAL(1,listIsFull(list));
	
	listDel(list);
}

void test_listIsEmpty_should_return_0_for_not_full_list()
{
	List *list = listNew(6);
	
	TEST_ASSERT_EQUAL(0,listIsFull(list));
	
	listDel(list);
}

void test_listNew_given_6_should_allotcate_list_object_with_a_buffer_of_6()
{
	List *list = listNew(6);
	TEST_ASSERT_NOT_NULL(list);
	TEST_ASSERT_NOT_NULL(list->buffer);
	TEST_ASSERT_EQUAL(6,list->length);
	TEST_ASSERT_EQUAL(0,list->size);

	listDel(list);
}

void test_listAdd_given_1_2_3_should_add_1_2_3_to_the_list_and_return_size_3()
{
	List *list = listNew(6);
	
	CEXCEPTION_T err;
	Try
	{
		listAdd(list,1);
		listAdd(list,2);
		listAdd(list,3);
	}
	
	Catch(err)
	{
		TEST_FAIL_MESSAGE("Error should not generate exception ");	
	}
		TEST_ASSERT_EQUAL(1,*(list->buffer));
		TEST_ASSERT_EQUAL(2,*(list->buffer)+1);
		TEST_ASSERT_EQUAL(3,*(list->buffer)+2);
		TEST_ASSERT_EQUAL(3,list->size);
	
	listDel(list);
}

void test_listAdd_given_1_2_3_4_5_6_7_should_add_123456_to_the_list_return_size_6_and_throw_error()
{
	List *list = listNew(6);
	
	CEXCEPTION_T err;
	Try
	{
		listAdd(list,1);
		listAdd(list,2);
		listAdd(list,3);
		listAdd(list,4);
		listAdd(list,5);
		listAdd(list,6);
		listAdd(list,7);
		TEST_FAIL_MESSAGE("Error should generate exception due to full list");	
	}
	
	Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_LIST_FULL,err);
		printf("Error [%d] : List is full",err);
	}
	TEST_ASSERT_EQUAL(1,*(list->buffer));
	TEST_ASSERT_EQUAL(2,*(list->buffer)+1);
	TEST_ASSERT_EQUAL(3,*(list->buffer)+2);
	TEST_ASSERT_EQUAL(4,*(list->buffer)+3);
	TEST_ASSERT_EQUAL(5,*(list->buffer)+4);
	TEST_ASSERT_EQUAL(6,*(list->buffer)+5);

	TEST_ASSERT_EQUAL(6,list->size);
	
	listDel(list);
}

void test_listRemove_x1_should_return_11_size_2()
{
	List *list = listNew(6);
	
	CEXCEPTION_T err;
	Try
	{	
		listAdd(list,11);
		listAdd(list,12);
		listAdd(list,13);
		
		TEST_ASSERT_EQUAL(11,listRemove(list));
		TEST_ASSERT_EQUAL(2,list->size);
	}
	Catch(err)
	{
		TEST_FAIL_MESSAGE("Error should not generate exception ");	
	}
	listDel(list);
}

void test_listRemove_x4_should_return_21_22_23_size_0_throw_error()
{
	List *list = listNew(6);
	
	CEXCEPTION_T err;
	Try
	{	
		listAdd(list,21);
		listAdd(list,22);
		listAdd(list,23);
		
		TEST_ASSERT_EQUAL(21,listRemove(list));
		TEST_ASSERT_EQUAL(22,listRemove(list));
		TEST_ASSERT_EQUAL(23,listRemove(list));
		listRemove(list);
		TEST_FAIL_MESSAGE("Error should generate exception due to empty list");	
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL(ERR_LIST_EMPTY,err);
		printf("Error [%d] : List is empty",err);
	}
	TEST_ASSERT_EQUAL(0,list->size);
	listDel(list);
}