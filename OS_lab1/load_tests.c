#include "stdafx.h"
#include <malloc.h>
#include "load_tests.h"
#include "mmemory.h"
#include "blocks.h"

void start_load_test(int kol_block, int all_memory, int iter, int max_size_of_block)
{
	VA *array = (VA*)malloc(all_memory * sizeof(VA));
	initial_meshing(array, kol_block, all_memory);
	fragmentation(array, kol_block, all_memory, iter, max_size_of_block);
}

void  fragmentation(VA* array, int kol_block, int all_memory, int iter, int max_size_of_block)
{
	int size;
	int num;
	int error;
	int size_dop = 0;
	int array_size = kol_block;
	bool flag = false;
	if (all_memory%kol_block != 0)array_size++;
	for (int i = 0; i < iter; i++)
	{
		VA new_ptr;
		do { //������ ������
			size = rand() % (max_size_of_block + 1);

			if (size != 0 && find_free_ptr(array, array_size, size) >= 0) //���� ����� ������ �� 0 ���� � ����� ���������� ��������� ����
			{
				num = find_free_ptr(array, array_size, size); //����� ����������� ���������� �����

				if (size_of_block(array[num]) != (-1)*size) //���� ������ ���������� ����� ������ ��� �� ���������� ������ ������� �� ����� ������
				{
					right_array_shift(array, array_size, num);//����������� ������ �� ���� �������
					error = _malloc(&new_ptr, size);//�������� ������
					array[num] = new_ptr;//���������� ��������� �� ���� � ������
					array[num+1] = new_ptr + size; //���������� ��������� �� ������� �����(+����� ����) ������� �������
					array_size++;
				}
				else //���� ������ ���������� ����� ��������� � ��� ������ ������� �� ����� ������
				{
					error = _malloc(&new_ptr, size); //�������� ������
					array[num] = new_ptr;//������� ��������� � ������
				}
			}
			else error = -3;

		} while (error != 0);
		//show(array,array_size);
		do {//����������� ������
			num = rand() % array_size;
		} while (ptr_of_free_block(array[num]) == 1); //���� ������� ����

		if (ptr_of_free_block(array[num + 1]) == 1) //���� ������ �� ���������� �������� ����� ���� - ��������
		{
			left_array_shift(array, array_size, num + 1); //�������� ������ �����(������� ��������� �� ���� ��������� ����)
			array_size--;
		}
		if (ptr_of_free_block(array[num-1]) == 1)//���� ����� �� ���������� �������� ����� ���� - ��������
		{
			size_dop = size_of_block(array[num-1]); //���������� ��� ������
			left_array_shift(array, array_size, num-1);//�������� ������ �����(������� ��������� �� ���� ��������� ����)
			array_size--;
			num--;
		}//�.� ������� ������ ���/��� �����
		_free(array[num]); //����������� ������
		array[num] += size_dop; //�������� ��������� �� ������ �����
		size_dop = 0;
		//show(array, array_size);
	}
	show(array, array_size);
	double res = (1 - (double)max_free_area() / count_free_area()) * 100;
	printf("%d %d %f\n", max_free_area(), count_free_area(), res);
}



void right_array_shift(VA* array, int array_size, int num)//����� ������� �� ���� ������� ������ � �������� num
{
	for (int i = array_size; i >num; i--)
	{

		array[i] = array[i - 1];
	}
}

void left_array_shift(VA* array, int array_size, int num) //����� ������� �� ���� ������� ����� � �������� num+1
{
	for (int i = num; i < array_size; i++)
	{
		if (i < array_size - 1)
			array[i] = array[i + 1];
	}
}

int count_free_area() //��� ���� ��������� ������
{
	int count = 0;
	for (int i = 0; i < block_quantity; i++)
		if (memory[i].is_free)
		{
			count += memory[i].szBlock;
		}

	return count;
}

int max_free_area() //������������ ������ ���������� �����
{
	int max = 0;

	for (int i = 0; i <block_quantity; i++)
		if (memory[i].szBlock>max && memory[i].is_free)
		{

			max = memory[i].szBlock;
		}

	return max;
}

void initial_meshing(VA* array, int kol_block, int all_memory)//��������� ������
{
	_init(1, all_memory);
	for (int i = 0; i < kol_block; i++)
		_malloc(&array[i], all_memory / kol_block);
	if (all_memory%kol_block != 0)_malloc(&array[kol_block], all_memory-all_memory / kol_block*kol_block);

	for (int i = 0; i < kol_block; i += 2)
	{
		_free(array[i]);
	}
}

void show(VA* array, int array_size) //����� ���� ������
{
	for (int i = 0; i < array_size; i++)
	{
		printf("|");
		printf("%d", size_of_block(array[i]));

	}
	printf(" \n");
}

bool ptr_of_free_block(VA ptr) { //�������� �� ������ ����
	for (int i = 0; i < block_quantity; i++)
		if (memory[i].ptr == ptr)
		{
			if (memory[i].is_free) return true;
			else return false;
		}

	return false;
}

int size_of_block(VA ptr) { //������ �����
	for (int i = 0; i < block_quantity; i++)
		if (memory[i].ptr == ptr) //���� ������ �� + ���� �������� �����
		{
			if (!memory[i].is_free)
				return memory[i].szBlock;
			else return memory[i].szBlock*(-1);
		}

	return 0;
}

int find_free_ptr(VA* array, int array_size, int size) //����� ������ ��������� � ���������� �� ������� ���� ������
{
	VA ptr_null = NULL;
	for (int i = 0; i < array_size; i++)
		if (ptr_of_free_block(array[i]) == 1 && (-1)*size_of_block(array[i]) >= size)
			return i;
	return -1;
}



/*

void start_load_test_rand(int kol_block, int all_memory, int iter, int max_size_of_block)
{
VA *array = (VA*)malloc(all_memory * sizeof(VA));
initial_meshing_rand(array, kol_block, all_memory);
fragmentation(array, kol_block, all_memory, iter, max_size_of_block);
}


void initial_meshing_rand(VA* array, int kol_block, int all_memory) //��������� ������(���������)
{
int fill_size = 0;
int all_fill_area = 0;
int k = 14;//����������� - �� ������� ��� ���������� ������ ���� ����� ��� ��� ������
int error;
_init(1, all_memory);
for (int i = 0; i < kol_block; i++) {
do {
fill_size = rand() % (all_memory / k + 1);

if ((i != kol_block - 1 && all_memory - all_fill_area - fill_size >0
&& (all_memory - all_fill_area - fill_size) / (kol_block - i - 1) != 0)
&& all_memory-all_fill_area-fill_size<=(kol_block-i-1)*((all_memory / k + 1)-1)
|| (i == kol_block - 1 && all_memory - all_fill_area == fill_size))
{
error = _malloc(&array[i], fill_size);
all_fill_area += fill_size;
}
else error = -3;

} while (error != 0);
}
for (int i = 0; i < kol_block; i += 2)
{
_free(array[i]);
}
}*/




