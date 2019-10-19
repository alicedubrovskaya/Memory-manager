#include "stdafx.h"
#include "blocks.h"
#include "mmemory.h"
#include "read_tests.h"
#include <assert.h>
#include <malloc.h>
void read_test_INCORRECT_PARAMETERS_ERROR1()
{
	VA pointer1=NULL;
	size_t size_buf = 10;
	VA buffer = (VA)malloc(sizeof(char)*size_buf);
	
	int returned_value = _read(pointer1, buffer, size_buf);

	int expected_value = INCORRECT_PARAMETERS_ERROR;
	assert(expected_value == returned_value);
}

void read_test_INCORRECT_PARAMETERS_ERROR2()
{
	VA pointer1;
	size_t size_buf = 10;
	_init(5, 10);
	_malloc(&pointer1, 10);
	VA buffer = NULL;

	int returned_value = _read(pointer1, buffer, size_buf);

	int expected_value = INCORRECT_PARAMETERS_ERROR;
	assert(expected_value == returned_value);
}

void read_test_INCORRECT_PARAMETERS_ERROR3()
{
	VA pointer1;
	size_t size_buf = 0;
	_init(5, 10);
	_malloc(&pointer1, 10);

	VA buffer = (VA)malloc(sizeof(char)*8);

	int returned_value = _read(pointer1, buffer, size_buf);

	int expected_value = INCORRECT_PARAMETERS_ERROR;
	assert(expected_value == returned_value);
}

void read_test_INCORRECT_PARAMETERS_ERROR4()
{
	//VA pointer1;
	size_t size_buf = 8;
	_init(5, 10);
	//_malloc(&pointer1, 10);

	VA buffer = (VA)malloc(sizeof(char) * size_buf);
	VA pointer2 = (VA)malloc(sizeof(char) * size_buf);

	int returned_value = _read(pointer2, buffer, size_buf);

	int expected_value = INCORRECT_PARAMETERS_ERROR;
	assert(expected_value == returned_value);
}

void read_test_INCORRECT_PARAMETERS_ERROR5()
{
	VA pointer1;
	size_t size_buf = 8;
	_init(5, 10);
	_malloc(&pointer1, 10);

	VA buffer = (VA)malloc(sizeof(char) * size_buf);

	int returned_value = _read(pointer1+10, buffer, size_buf);

	int expected_value = INCORRECT_PARAMETERS_ERROR;
	assert(expected_value == returned_value);
}
void read_test_UNKNOWN_ERROR()
{
	VA pointer1;

	_init(5, 10);
	_malloc(&pointer1, 10);
	VA new_buf;
	new_buf = (char*)malloc(sizeof(char)*7);
	if (memory != NULL) 
	{
		free(memory);
		memory = NULL;
	}
	int returned_value = _read(pointer1, new_buf, 7);
	int expected_value = UNKNOWN_ERROR;
	assert(expected_value == returned_value);
}

void read_test_OUT_OF_BOUNDS_ERROR()
{
	_init(3, 10);
	VA pointer1;
	_malloc(&pointer1, 5);
	VA new_buf = (char*)malloc(sizeof(char) * 7);
	int returned_value = _read(pointer1, new_buf, 7);
	int expected_value = OUT_OF_BOUNDS_ERROR;
	assert(expected_value == returned_value);
}

void read_test_SUCCESSFUL_IMPLEMENTATION1()
{
	VA pointer1;
	
	_init(5, 10);
	_malloc(&pointer1, 10);
	
	char *buffer = "11223344";
	size_t size_buf = strlen(buffer)+1;

	_write(pointer1, buffer, size_buf);

	VA new_buf;
	new_buf = (char*)malloc(sizeof(char)*size_buf);
	int returned_value = _read(pointer1, new_buf, size_buf-5);

	int expected_value = SUCCESSFUL_IMPLEMENTATION;
	assert(expected_value == returned_value);
 }

void read_test_SUCCESSFUL_IMPLEMENTATION2()
{
	VA pointer1;
	VA pointer2;

	_init(5, 10);
	_malloc(&pointer1, 10);
	_malloc(&pointer2, 15);

	char *buffer1 = "first";
	size_t size_buf1 = strlen(buffer1) + 1;

	char *buffer2 = "second";
	size_t size_buf2 = strlen(buffer2) + 1;

	_write(pointer1, buffer1, size_buf1);
	_write(pointer2, buffer2, size_buf2);

	VA new_buf;
	new_buf = (char*)malloc(sizeof(char)*(size_buf1+size_buf2));
	_read(pointer1, new_buf, size_buf1);
	int returned_value = _read(pointer2, new_buf+size_buf1-1, size_buf2);

	int expected_value = SUCCESSFUL_IMPLEMENTATION;
	assert(expected_value == returned_value);
}

void read_all_tests()
{
	read_test_INCORRECT_PARAMETERS_ERROR1();
	read_test_INCORRECT_PARAMETERS_ERROR2();
	read_test_INCORRECT_PARAMETERS_ERROR3();
	read_test_INCORRECT_PARAMETERS_ERROR4();
	read_test_INCORRECT_PARAMETERS_ERROR5();
	read_test_OUT_OF_BOUNDS_ERROR();
	read_test_SUCCESSFUL_IMPLEMENTATION1();
	read_test_SUCCESSFUL_IMPLEMENTATION2();
	read_test_UNKNOWN_ERROR();
}