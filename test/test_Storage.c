#include "unity.h"
#include "ErrorCode.h"
#include "Storage.h"
#include "mock_List.h"
#include "CException.h"

List list ;

void setUp(void)
{
	int listbuffer[20];
	
	list.buffer = listbuffer;
	list.length = 512;
	list.size = 0;
	
}

void tearDown(void)
{
}

void test_store_given_5_6_7_should_return_5_6_7(void)
{
	CEXCEPTION_T err;

	int integers[] = {5,6,7};

	Try
	{
		listIsFull_ExpectAndReturn(&list,0);
		listAdd_Expect(&list,5);
		listIsFull_ExpectAndReturn(&list,0);
		listAdd_Expect(&list,6);
		listIsFull_ExpectAndReturn(&list,0);
		listAdd_Expect(&list,7);
	
		store(&list,integers,3);
		
	}
	Catch(err)
	{
		TEST_FAIL_MESSAGE("Do not expect exception to be generated.");
	}
	
}

void test_store_given_10_11_12_should_return_10_11_and_err(void)
{
	CEXCEPTION_T err;

	int integers[] = {10,11,12};
	Try
	{
		listIsFull_ExpectAndReturn(&list,0);
		listAdd_Expect(&list,10);
		listIsFull_ExpectAndReturn(&list,0);
		listAdd_Expect(&list,11);
		
		listIsFull_ExpectAndReturn(&list,1);
		
		store(&list,integers,3);
		
		TEST_FAIL_MESSAGE("Error should generate exception due to full list");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL(err,ERR_LIST_FULL);
		printf("Error [%d]: List is full \n",err);
	}
	
	
}



void test_retrieve_given_21_22_23_24_25_should_return_21_22_23_24_25_to_storedIntegers(void)
{
	int integers[] = {21,22,23,24,25};
	int storedIntegerSize;
	int *storedIntegers;
	int i ;
	CEXCEPTION_T err;
	Try
	{
		listIsEmpty_ExpectAndReturn(&list,0);
		
		listIsEmpty_ExpectAndReturn(&list,0);
		listRemove_ExpectAndReturn(&list,21);
	
		listIsEmpty_ExpectAndReturn(&list,0);
		listRemove_ExpectAndReturn(&list,22);
	
		listIsEmpty_ExpectAndReturn(&list,0);
		listRemove_ExpectAndReturn(&list,23);
	
		listIsEmpty_ExpectAndReturn(&list,0);
		listRemove_ExpectAndReturn(&list,24);
	
		listIsEmpty_ExpectAndReturn(&list,0);
		listRemove_ExpectAndReturn(&list,25);
	
		listIsEmpty_ExpectAndReturn(&list,1);
		
		storedIntegers = retrieve(&list,&storedIntegerSize);
		
	
		for ( i = 0 ; i < storedIntegerSize ; i ++ )
			printf("Stored Integer %d : %d\n",(i+1),storedIntegers[i]);
	
	}
	Catch(err)
	{
		TEST_FAIL_MESSAGE("Do not expect exception to be generated.");
	}
	
	
	
}

void test_retrieve_given_list_empty_should_return_err(void)
{
	int integers[] = {31,32,33,34,35};
	int storedIntegerSize;
	int *storedIntegers;
	int i ;
	CEXCEPTION_T err;
	Try
	{
		listIsEmpty_ExpectAndReturn(&list,1);
		
		storedIntegers = retrieve(&list,&storedIntegerSize);
		
		TEST_FAIL_MESSAGE("Error should generate exception due to empty list");
		for ( i = 0 ; i < storedIntegerSize ; i ++ )
			printf("Stored Integer %d : %d\n",(i+1),storedIntegers[i]);	
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL(err,ERR_LIST_EMPTY);
		printf("Error [%d] : List is empty.",err);
	}
	
	
	
}
