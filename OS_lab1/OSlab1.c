// ConsoleApplication12.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <malloc.h>

#include "init_tests.h"
#include "malloc_tests.h"
#include "free_tests.h"
#include "load_tests.h"
#include "all_tests.h"
#include "mmemory.h"

#pragma warning(disable : 4996)

int main() //освобождение памяти
{
	/*start_load_test(300, 5000, 20);
	start_load_test(300, 5000, 50);
	start_load_test(300, 5000, 100);
	start_load_test(300, 5000, 200);
	start_load_test(300, 5000, 500);
	start_load_test(300, 5000, 5000);
	start_load_test(300, 5000, 50000);
	start_load_test(300, 5000, 5000000);
	start_load_test(300, 5000, 5000000000);
	*/
	//не нашла еще закономерность
	start_load_test(30, 50, 5000, 2000);
	start_load_test(30, 100, 5000, 2000);
	start_load_test(30, 500, 5000, 2000);
	start_load_test(30, 1000, 5000, 2000);
	start_load_test(30, 1500, 5000, 2000);
	start_load_test(30, 5000, 5000, 2000);
	start_load_test(30, 10000, 5000, 2000);
	
/*
	//тест на изменение количества начальных блоков
	start_load_test(10, 5000, 10000,500);
	start_load_test(50, 5000, 10000,500);
	start_load_test(150, 5000, 10000,500);
	start_load_test(500, 5000, 10000,500);
	start_load_test(1000, 5000, 10000,500);
	*\
	/* тест на изменение размеров вкладываемых блоков в память
	start_load_test(50, 50000, 10000, 50);
	start_load_test(50, 50000, 10000, 100);
	start_load_test(50, 50000, 10000, 500);
	start_load_test(50, 50000, 10000, 1000);
	start_load_test(50, 50000, 10000, 2000);
	start_load_test(50, 50000, 10000, 5000);
	start_load_test(50, 50000, 10000, 6000);*/
	_init(8, 4);
	VA ptr;
	_malloc(&ptr, 20);
	VA ptr2;
	_malloc(&ptr2, 3);
	VA buffer = "112233445566";
	_write(ptr + 3, buffer, 12);
	VA buffer1=(char*)malloc(5*sizeof(char));
	int ret = memcmp(buffer + 4, buffer1, 5);
	//assert(ret == 0);
	_read(ptr + 7, buffer1, 5);
	char s1[6];
	char s[5];
	memcpy(s, buffer+4, 5);
	//s[5] = 0;
	memcpy(s1, buffer1, 5);
	s1[5] = 0;
	//init_tests();
	//loadTests();
return 0;
}

