#pragma once

#include "mmemory.h"
#include <stdbool.h>
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

