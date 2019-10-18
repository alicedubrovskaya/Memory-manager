#include "stdafx.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "mmemory.h"
#include "blocks.h"
#include "free_tests.h"

void free_test_UNKNOWN_ERROR() {
	_init(4, 10);
	VA pointer;
	_malloc(&pointer, 10);
	if (memory != NULL || first_pointer != NULL) //ПО-ДРУГОМУ
	{
		free(memory); //освобождаем память
		free(first_pointer);
		first_pointer = NULL;
		memory = NULL;
	}
	int returned_value = _free(pointer);
	int expected_value = UNKNOWN_ERROR;
	assert(expected_value == returned_value);
}

void free_test_INCORRECT_PARAMETERS_ERROR() {
	_init(6, 8);
	VA pointer = (VA)malloc(9);
	int returned_value = _free(pointer); //там будет memory[i].isfree=true => условие не выполнится и ошибка
	int expected_value = INCORRECT_PARAMETERS_ERROR;
	assert(expected_value == returned_value);
}


void free_test_SUCCESSFUL_IMPLEMENTATION1() {
	_init(4, 10);
	VA pointer;
	_malloc(&pointer, 10);

	int returned_value = _free(pointer);
	int expected_value = SUCCESSFUL_IMPLEMENTATION;
	assert(expected_value == returned_value);
}

void free_test_SUCCESSFUL_IMPLEMENTATION2() {
	_init(3, 10);
	VA pointer1;
	VA pointer2;
	VA pointer3;
	VA pointer4;

	_malloc(&pointer1, 5);
	_malloc(&pointer2, 10);
	_malloc(&pointer3, 6);
	_malloc(&pointer4, 4);

	_free(pointer2);
	_free(pointer4);
	int returned_value = _free(pointer3);

	int expected_value = SUCCESSFUL_IMPLEMENTATION;
	assert(expected_value == returned_value);
}

void free_test_SUCCESSFUL_IMPLEMENTATION3() {
	_init(5, 5);
	VA pointer1;
	VA pointer2;
	VA pointer3;
	VA pointer4;

	_malloc(&pointer1, 6);
	_malloc(&pointer2, 2);
	_malloc(&pointer3, 12);
	_malloc(&pointer4, 5);

	_free(pointer1);
	_malloc(&pointer1, 1);

	int returned_value = _free(pointer4);

	int expected_value = SUCCESSFUL_IMPLEMENTATION;
	assert(expected_value == returned_value);
}

void free_all_tests()
{
	free_test_UNKNOWN_ERROR();
	free_test_INCORRECT_PARAMETERS_ERROR();

	free_test_SUCCESSFUL_IMPLEMENTATION1();
	free_test_SUCCESSFUL_IMPLEMENTATION2();
	free_test_SUCCESSFUL_IMPLEMENTATION3();
}
