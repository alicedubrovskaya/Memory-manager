// ConsoleApplication12.cpp: ���������� ����� ����� ��� ����������� ����������.
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

#pragma warning(disable : 4996)

int main() //������������ ������
{
	
	init_tests();
	loadTests();
return 0;
}

