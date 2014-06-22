#include "unity.h"
#include "ErrorCode.h"
#include "Storage.h"
#include "List.h"
#include "CException.h"

List list ;

void setUp(void)
{
}

void tearDown(void)
{
}

void test_store_given_5_6_7_should_return_5_6_7(void)
{
	CEXCEPTION_T err;
	
	List *list = listNew(6);
	
	int integers[] = {5,6,7};

	Try
	{
		store(list,integers,3);
		
	}
	Catch(err)
	{
		TEST_FAIL_MESSAGE("Do not expect exception to be generated.");
	}
	
	TEST_ASSERT_EQUAL(5,*(list->buffer));
	TEST_ASSERT_EQUAL(6,*(list->buffer)+1);
	TEST_ASSERT_EQUAL(7,*(list->buffer)+2);

	listDel(list);
}

void test_store_given_15_16_17_18_19_20_21_should_return_15_16_17_18_19_20_and_error(void)
{
	CEXCEPTION_T err;
	
	List *list = listNew(6);
	
	int integers[] = {15,16,17,18,19,20,21};

	Try
	{
		store(list,integers,7);
		TEST_FAIL_MESSAGE("Error should generate exception due to full list.");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL(err,ERR_LIST_FULL);
		printf("Error [%d] : List is full",err);
	}
	
	TEST_ASSERT_EQUAL(15,*(list->buffer));
	TEST_ASSERT_EQUAL(16,*(list->buffer)+1);
	TEST_ASSERT_EQUAL(17,*(list->buffer)+2);
	TEST_ASSERT_EQUAL(18,*(list->buffer)+3);
	TEST_ASSERT_EQUAL(19,*(list->buffer)+4);
	TEST_ASSERT_EQUAL(20,*(list->buffer)+5);

	listDel(list);
}

void test_retrieve_given_21_22_23_should_return_21_22_23()
{
	CEXCEPTION_T err;
	
	List *list = listNew(6);
	
	int storedIntegerSize;
	int *storedIntegers;
	int i ;
	int integers[] = {21,22,23};

	Try
	{
		store(list,integers,3);
		TEST_ASSERT_EQUAL(21,*(list->buffer));
		TEST_ASSERT_EQUAL(22,*(list->buffer)+1);
		TEST_ASSERT_EQUAL(23,*(list->buffer)+2);
		storedIntegers = retrieve(list,&storedIntegerSize);
	
		for ( i = 0 ; i < storedIntegerSize ; i ++ )
			printf("Stored Integer %d : %d\n",(i+1),storedIntegers[i]);
	}
	Catch(err)
	{
		TEST_FAIL_MESSAGE("Do not expect exception to be generated.");
	}
	
	listDel(list);
}
