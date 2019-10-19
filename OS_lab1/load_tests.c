#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include "load_tests.h"
#include "mmemory.h"

#pragma warning(disable : 4996)
#define _POSIX_C_SOURCE 199309L


void loadTests() {
	FILE *fp;
	fp = fopen("D:\\уник\\3 к\\rep\\Memory-manager\\test.txt", "w+");
	long t;
	time_t actual_time, actual_time1;
	double actual_time_sec;

	struct timespec mt1, mt2;
	//Переменная для расчета дельты времени
	long int tt;

	int pageNumber = 5;
	int pageSize = 8;

	_init(pageNumber, pageSize);
	VA va;
	actual_time1 = clock();
	char *z = NULL;
	char a = 'a';
	for (unsigned infoSize = 1; infoSize <= pageSize * pageNumber; infoSize++) {
		printf("%d\n", infoSize);
	
		z =(char*) malloc(infoSize* sizeof(char));

 		for (unsigned i = 0; i < infoSize; i++) {
		
			z[i] = a;
		}
		t = GetTickCount();
		//clock_gettime(CLOCK_REALTIME, &mt1);
		_malloc(&va, infoSize);
		_write(va, z, infoSize);
		_free(va);
		t = GetTickCount()-t;
		//clock_gettime(CLOCK_REALTIME, &mt2);

		//_read(va,z,pageToAddNumber*pageSize);
		//actual_time_sec = difftime(actual_time, actual_time1);
		printf("%f\n", t);
		fprintf(fp, "%d;%.0f\n", infoSize, t);
		a++;
	}
	free(z);
	pageSize = 2;
	pageNumber = 20;
	a = 'a';
	_init(pageNumber, pageSize);
	for (int infoSize = 1; infoSize <= pageSize * pageNumber; infoSize++) {
		printf("%d\n", infoSize);
		z = calloc(infoSize, sizeof(char));
		for (int i = 0; i < infoSize; ++i) {
			z[i] = a;
		}
		
		_malloc(&va, infoSize);
		_write(va, z, infoSize);
		_free(va);
		actual_time = clock();
		//_read(va,z,pageToAddNumber*pageSize);
		actual_time_sec = difftime(actual_time, actual_time1);
		
		//fprintf(fp, "%d;%f\n", infoSize, actual_time_sec);
		a++;
	}
	actual_time = clock();
	printf("It took me %d clicks (%f seconds).\n",
		(int)actual_time_sec, ((double)actual_time_sec) / CLOCKS_PER_SEC);
	fclose(fp);
}
