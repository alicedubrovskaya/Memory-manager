// ConsoleApplication12.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <malloc.h>
#define INCORRECT_PARAMETERS_ERROR -1;
#define UNKNOWN_ERROR 1;
#define NOT_ENOUGH_MEMORY_ERROR -2;
#define OUT_OF_BOUNDS_ERROR - 2;
#define SUCCESSFUL_IMPLEMENTATION 0;


typedef char* VA;

struct block {
	size_t szBlock; //размер блока, size_t – целочисленный беззнаковый тип
	VA ptr; //адрес блока
	bool is_free; // свободен ли блок
};

struct block *memory; //наша память
int all_memory; //n*szPage
int block_quantity; // количество блоков или размер массива
VA first_pointer;

int create_new_block(size_t szBlock, int block_num) //создадим новый блок из оставшейся памяти
{
	struct block new_block;
	new_block.is_free = true;
	new_block.szBlock = szBlock;
	new_block.ptr = memory[block_num].ptr + memory[block_num].szBlock; //новый указатель сдвинут от старого на размер занятой памяти

	for (int i = block_quantity; i > block_num; i--) //сдвинем массив на 1, так как у нас появляется новый блок
	{
		if (i == block_num + 1) memory[i] = new_block;
		else
			memory[i] = memory[i - 1];
	}
	block_quantity++;
}

int _malloc(VA* ptr, size_t szBlock)
{
	bool area_is_find = false;

	if (szBlock == 0)
		return INCORRECT_PARAMETERS_ERROR; //если размер блока равен 0, мы ничего не можем сделать с ним

	if (memory == NULL)
		return UNKNOWN_ERROR; // отсутствие блоков в массиве


	for (int i = 0; i < block_quantity; i++)
	{
		if (memory[i].szBlock >= szBlock && memory[i].is_free) //если нашли свободный блок подходящего размера
		{
			int new_size_block = memory[i].szBlock - szBlock; // находим лишнюю память
			memory[i].is_free = false; //присваиваем статус занятого
			memory[i].szBlock = szBlock; //указываем новый размер
			*ptr = memory[i].ptr;
			if (new_size_block > 0) create_new_block(new_size_block, i);
			area_is_find = true;
			break;
		}
	}
	if (!area_is_find)
		return NOT_ENOUGH_MEMORY_ERROR; //не найден подходящий блок
	return SUCCESSFUL_IMPLEMENTATION; //функция успешно выполнена
}

void combine_blocks(int i) //когда объединяем два блока памяти в один, смещение происходит
{
	for (int c = i; c < block_quantity; c++) //смещаем блоки на один влево
		memory[c] = memory[c + 1];
	block_quantity--;
}


int _free(VA ptr) {
	if (memory == NULL)
		return UNKNOWN_ERROR;

	bool area_is_find = false;

	for (int i = 0; i < block_quantity; i++) {
		if (memory[i].ptr == ptr && !memory[i].is_free) {
			memory[i].is_free = true;

			if (memory[i - 1].is_free && i > 0) {
				memory[i - 1].szBlock += memory[i].szBlock; //прибавляем к размеру предыдущего блока размер текущего
				combine_blocks(i);
				if (memory[i].is_free) {
					memory[i - 1].szBlock += memory[i].szBlock; //объединяем два блока
					combine_blocks(i);
				}
			}
			else
				if (memory[i + 1].is_free) {
					memory[i].szBlock += memory[i + 1].szBlock;
					combine_blocks(i + 1);
				}

			area_is_find = true;
			break;
		}
	}
	if (!area_is_find)
		return INCORRECT_PARAMETERS_ERROR;

	return SUCCESSFUL_IMPLEMENTATION;
}


int error_checking(VA ptr, void* pBuffer, size_t szBuffer)
{
	bool is_find = false;

	if (ptr == NULL || pBuffer == NULL || szBuffer <= 0)
	{
		return INCORRECT_PARAMETERS_ERROR;
	}

	if (memory == NULL)
	{
		return UNKNOWN_ERROR
	}

	for (int i = 0; i < block_quantity; i++)
	{
		if (ptr >= memory[i].ptr && ptr < memory[i].ptr + memory[i].szBlock)
		{
			if (memory[i].ptr + memory[i].szBlock - ptr<szBuffer)
				return OUT_OF_BOUNDS_ERROR;

			if (memory[i].is_free)
				is_find = true;
		}
	}
	if (!is_find)
		return INCORRECT_PARAMETERS_ERROR;
	return SUCCESSFUL_IMPLEMENTATION;
}

int _write(VA ptr, void* pBuffer, size_t szBuffer)
{
	switch (error_checking(ptr, pBuffer, szBuffer)) {
	case 0:
		memcpy(ptr, pBuffer, szBuffer);
		return SUCCESSFUL_IMPLEMENTATION;
	case -1:
		return INCORRECT_PARAMETERS_ERROR;
	case -2:
		return OUT_OF_BOUNDS_ERROR;
	default:
		return UNKNOWN_ERROR;
	}

}

int _read(VA ptr, void* pBuffer, size_t szBuffer)
{
	switch (error_checking(ptr, pBuffer, szBuffer)) {
	case 0:
		memcpy(pBuffer, ptr, szBuffer);
		return SUCCESSFUL_IMPLEMENTATION;
	case -1:
		return INCORRECT_PARAMETERS_ERROR;
	case -2:
		return OUT_OF_BOUNDS_ERROR;
	default:
		return UNKNOWN_ERROR;

	}
}


int _init(int n, int szPage) //Инициализация модели менеджера памяти
{
	block_quantity = 1;

	// n- количество страниц
	//szPage размер страницы

	if (n <= 0 || szPage <= 0)
		return INCORRECT_PARAMETERS_ERROR;

	if (memory != NULL || first_pointer != NULL) //ПО-ДРУГОМУ
	{
		free(memory); //освобождаем память
		free(first_pointer);
		first_pointer = NULL;
		memory = NULL;
	}


	all_memory = n * szPage; //количество кусочков памяти или вся память

	memory = (struct block*)malloc(all_memory * sizeof(struct block));//выделяем память для нашего массива
	if (memory == NULL) return UNKNOWN_ERROR; //ошибка, значит память не выделилась


	first_pointer = (VA)malloc(all_memory); // выделяем память для первого блока
	if (first_pointer == NULL) return UNKNOWN_ERROR; //ошибка, значит память не выделилась


	struct block first_block; //создаем первый блок
	first_block.ptr = first_pointer; // адрес этого блока 
	first_block.is_free = true;
	first_block.szBlock = all_memory;//размер этого блока - вся память
	memory[block_quantity - 1] = first_block;
	return SUCCESSFUL_IMPLEMENTATION;

}

void free_test_UNKNOWN_ERROR() {
	assert(block_quantity == 0); //??????то же самое что и с маллоком
}

void free_test_INCORRECT_PARAMETERS_ERROR() {
	_init(4, 10);
	VA pointer = (VA)malloc(12);
	int returned_value = _free(pointer); //там будет memory[i].isfree=true => условие не выполнится и ошибка
	int expected_value = INCORRECT_PARAMETERS_ERROR;
	assert(expected_value == returned_value);
}


void free_test_SUCCESSFUL_IMPLEMENTATION() {
	_init(4, 10);
	VA pointer;
	_malloc(&pointer, 10);

	int returned_value = _free(pointer);
	int expected_value = SUCCESSFUL_IMPLEMENTATION;
	assert(expected_value == returned_value);
}


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

void test_init_SUCCESSFUL_IMPLEMENTATION() {
	int expected_value = SUCCESSFUL_IMPLEMENTATION;
	int returned_value = _init(4, 2);
	assert(expected_value == returned_value);
}

void test_init_UNKNOWN_ERROR_1() {  //МАРРГО ДОБАВЬ НУЛИ ПРОВЕРЬ и first pointer
	int expected_value = UNKNOWN_ERROR;
	int returned_value = _init(4000000, 10000);
	assert(expected_value == returned_value);
}



void malloc_test_INCORRECT_PARAMETERS_ERROR() {

	_init(4, 10);
	VA pointer_for_malloc;


	int expected_value = INCORRECT_PARAMETERS_ERROR;
	int returned_value = _malloc(&pointer_for_malloc, 0);

	assert(expected_value == returned_value);
}

void malloc_test_UNKNOWN_ERROR() { //????????????????????логично, что memory NULL если в нем нет блоков, хотя не корректно
	assert(block_quantity == 0);
}

void malloc_test_NOT_ENOUGH_MEMORY_ERROR() {
	_init(4, 10);
	VA pointer_1;
	VA pointer_2;
	_malloc(&pointer_1, 10);
	_malloc(&pointer_2, 20);
	int returned_value = _malloc(&pointer_1, 20);  //20 не влезет в свободный блок, поэтому будет ошибка
	int expected_value = NOT_ENOUGH_MEMORY_ERROR;

	assert(returned_value == expected_value);
}

void malloc_test_SUCCESSFUL_IMPLEMENTATION() {
	_init(4, 10);
	VA pointer;
	int returned_value = _malloc(&pointer, 20);
	int expected_value = SUCCESSFUL_IMPLEMENTATION;
	assert(returned_value == expected_value);
}

void(*tests[])(void) = {
	malloc_test_NOT_ENOUGH_MEMORY_ERROR,
	malloc_test_INCORRECT_PARAMETERS_ERROR,
	malloc_test_SUCCESSFUL_IMPLEMENTATION
};

int main()
{
	// ТЕСТЫ ДЛЯ INIT

	//test_init_INCORRECT_PARAMETERS_ERROR_1();
	//test_init_INCORRECT_PARAMETERS_ERROR_2();
	//test_init_SUCCESSFUL_IMPLEMENTATION();
	//test_init_UNKNOWN_ERROR_1();

	/*
	ТЕСТЫ ДЛЯ MALLOC
	malloc_test_INCORRECT_PARAMETERS_ERROR();
	malloc_test_UNKNOWN_ERROR();
	malloc_test_NOT_ENOUGH_MEMORY_ERROR();
	malloc_test_SUCCESSFUL_IMPLEMENTATION();

	ТЕСТЫ ДЛЯ FREE
	free_test_UNKNOWN_ERROR();
	*/
	//free_test_INCORRECT_PARAMETERS_ERROR();
	//free_test_SUCCESSFUL_IMPLEMENTATION();

	for (int i = 0; i < 3; i++) {
		(*tests[i])();
	}


	return 0;
}

