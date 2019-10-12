
#include "stdafx.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "mmemory.h"
#include "blocks.h"
#include "read_tests.h"
void read_test_SUCCESSFUL_IMPLEMENTATION()
{
	VA pointer1;
	//VA pointer2;

	_init(5, 10);
	_malloc(&pointer1, 10);
	//_malloc(&pointer1, 15);

	char *buffer = "11223344";
	size_t size_buf = strlen(buffer)+1;

	_write(pointer1, buffer, size_buf);

	VA new_buf;
	new_buf = (char*)malloc(sizeof(char)*size_buf);
	int returned_value = _read(pointer1, new_buf, size_buf-5);

	int expected_value = SUCCESSFUL_IMPLEMENTATION;
	assert(expected_value == returned_value);
 }