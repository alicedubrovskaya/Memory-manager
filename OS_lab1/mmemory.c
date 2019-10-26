#include "stdafx.h"
#include "mmemory.h"
#include "blocks.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

void unit_blocks(int i) //когда объединяем два блока памяти в один, смещение происходит
{
	for (int c = i; c < block_quantity; c++) //смещаем блоки на один влево
		memory[c] = memory[c + 1];
	block_quantity--;
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

int _free(VA ptr) {
	if (memory == NULL)
		return UNKNOWN_ERROR;

	bool block_is_find = false;

	for (int i = 0; i < block_quantity; i++) {
		if (memory[i].ptr == ptr && !memory[i].is_free) {
			memory[i].is_free = true;

			if (memory[i + 1].is_free && i+1<block_quantity) { //ДОБАВИЛА УСЛОВИЕ И СОКРАТИЛА ФУНКЦИЮ - МАРГО
				memory[i].szBlock += memory[i + 1].szBlock;
				unit_blocks(i + 1);
			}

			if (memory[i - 1].is_free && i > 0) {
				memory[i - 1].szBlock += memory[i].szBlock; //прибавляем к размеру предыдущего блока размер текущего
				unit_blocks(i);	
			}
			
			block_is_find = true;
			break;
		}
	}
	if (!block_is_find)
		return INCORRECT_PARAMETERS_ERROR;

	return SUCCESSFUL_IMPLEMENTATION;
}

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
		if (ptr >= memory[i].ptr && ptr < memory[i].ptr + memory[i].szBlock && !memory[i].is_free)
		{
			if (memory[i].ptr + memory[i].szBlock - ptr<szBuffer)
				return OUT_OF_BOUNDS_ERROR;

			//if (memory[i].is_free)
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
	
	memset(first_pointer, '0', all_memory);
	if (first_pointer == NULL) return UNKNOWN_ERROR; //ошибка, значит память не выделилась


	struct block first_block; //создаем первый блок
	first_block.ptr = first_pointer; // адрес этого блока 
	first_block.is_free = true;
	first_block.szBlock = all_memory;//размер этого блока - вся память
	memory[block_quantity - 1] = first_block;
	return SUCCESSFUL_IMPLEMENTATION;

}