#include "stdafx.h"
#include "blocks.h"
#include "mmemory.h"
#include "malloc_tests.h"
#include <assert.h>

void malloc_test_INCORRECT_PARAMETERS_ERROR() {

	_init(7, 5);
	VA pointer_for_malloc;


	int expected_value = INCORRECT_PARAMETERS_ERROR;
	int returned_value = _malloc(&pointer_for_malloc, 0);

	assert(expected_value == returned_value);
}

void malloc_test_UNKNOWN_ERROR() { //????????????????????логично, что memory NULL если в нем нет блоков, хотя не корректно

	if (memory != NULL || first_pointer != NULL) //ПО-ДРУГОМУ
	{
		free(memory); //освобождаем память
		free(first_pointer);
		first_pointer = NULL;
		memory = NULL;
	}
	VA pointer_for_malloc;
	int expected_value = UNKNOWN_ERROR;
	int returned_value = _malloc(&pointer_for_malloc, 0);
}

void malloc_test_NOT_ENOUGH_MEMORY_ERROR() {
	_init(6, 15);
	VA pointer_1;
	VA pointer_2;
	_malloc(&pointer_1, 40);
	_malloc(&pointer_2, 45);
	int returned_value = _malloc(&pointer_1, 7);  // не влезет в свободный блок, поэтому будет ошибка
	int expected_value = NOT_ENOUGH_MEMORY_ERROR;

	assert(returned_value == expected_value);
}

void malloc_test_SUCCESSFUL_IMPLEMENTATION() {
	_init(6, 10);
	VA pointer;
	int returned_value = _malloc(&pointer, 20);
	int expected_value = SUCCESSFUL_IMPLEMENTATION;
	assert(returned_value == expected_value);
}

void malloc_all_tests()
{
	malloc_test_INCORRECT_PARAMETERS_ERROR();
	malloc_test_UNKNOWN_ERROR();
	malloc_test_NOT_ENOUGH_MEMORY_ERROR();
	malloc_test_SUCCESSFUL_IMPLEMENTATION();
}