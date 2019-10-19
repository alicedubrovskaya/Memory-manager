#include "stdafx.h"
#include "all_tests.h"

void init_tests()
{
	void(*tests[])() = {
		init_all_tests,
		malloc_all_tests,
		free_all_tests,
		write_all_tests,
		read_all_tests
	};

	for (int i = 0; i < 5; i++) {
		(*tests[i])();
	}
}
