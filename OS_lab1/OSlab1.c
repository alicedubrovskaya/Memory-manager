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
#include "all_tests.h"


int main() //������������ ������
{
	int x = 9;
	int i = 1;
	int f = 1;
	while (i <= x) {
		f *= i;
		i++;
	}
	init_tests();
return 0;
}

