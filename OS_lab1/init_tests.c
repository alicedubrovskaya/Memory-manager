#include "stdafx.h"
#include "mmemory.h"
#include "init_tests.h"
#include "blocks.h"
#include <assert.h>

void test_init_INCORRECT_PARAMETERS_ERROR_1() {
	int expected_value = INCORRECT_PARAMETERS_ERROR;
	int returned_value = _init(-5, 2);
	assert(expected_value == returned_value);
}

void test_init_INCORRECT_PARAMETERS_ERROR_2() {
	int expected_value = INCORRECT_PARAMETERS_ERROR;
	int returned_value = _init(2, -5);
	assert(expected_value == returned_value);
}

void test_init_SUCCESSFUL_IMPLEMENTATION1() {
	int expected_value = SUCCESSFUL_IMPLEMENTATION;
	int returned_value = _init(4, 2);
	assert(expected_value == returned_value);
}

void test_init_SUCCESSFUL_IMPLEMENTATION2() {
	test_init_SUCCESSFUL_IMPLEMENTATION1();
	test_init_SUCCESSFUL_IMPLEMENTATION1();
}

void test_init_UNKNOWN_ERROR_1() {  //люппцн днаюбэ мскх опнбепэ Х first pointer
	int expected_value = UNKNOWN_ERROR;
	int returned_value = _init(4000000, 10000);
	assert(expected_value == returned_value);
}

void init_all_tests()
{
	test_init_INCORRECT_PARAMETERS_ERROR_1();
	test_init_INCORRECT_PARAMETERS_ERROR_2();
	test_init_SUCCESSFUL_IMPLEMENTATION1();
	test_init_SUCCESSFUL_IMPLEMENTATION2();
	test_init_UNKNOWN_ERROR_1();
}