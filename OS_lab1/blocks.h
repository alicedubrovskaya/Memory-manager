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
	size_t szBlock; //������ �����, size_t � ������������� ����������� ���
	VA ptr; //����� �����
	bool is_free; // �������� �� ����
};

struct block *memory; //���� ������
int all_memory; //n*szPage
int block_quantity; // ���������� ������ ��� ������ �������
VA first_pointer;

