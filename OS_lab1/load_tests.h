
#pragma once
#include<stddef.h>
#include <stdbool.h>

typedef char* VA;

void start_load_test(int kol_block, int all_memory, int iter, int max_size_of_block);
void  fragmentation(VA* array, int kol_block, int all_memory, int iter, int max_size_of_block);
void initial_meshing(VA* array, int kol_block, int all_memory);
bool ptr_of_free_block(VA ptr);
int find_free_ptr(VA* array, int array_size, int size);
void show(VA* array, int array_size);
void left_array_shift(VA* array, int array_size, int num);
void right_array_shift(VA* array, int array_size, int num);
int max_free_area();
int count_free_area();


//void start_load_test_rand(int all_memory, int iter, int max_size_of_block);
//void initial_meshing_rand(VA* array, int kol_block, int all_memory);