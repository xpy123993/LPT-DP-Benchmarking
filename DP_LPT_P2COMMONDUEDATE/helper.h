#pragma once

#include "stdafx.h"

int randint(int _min, int _max)
{
	if (_min == _max) return _min;
	if (_min > _max) {
		printf("Random generator: min (%d) > max (%d)\n", _min, _max);
		exit(0);
	}
	return _min + rand() % (_max - _min);
}

int argmin(int* arr, int arr_size, bool non_negative = false)
{
	if (arr_size <= 0)
	{
		printf("Error: Argmin with <= 0 elements\n");
		exit(0);
	}
	int min_index = 0;
	for (int i = 1; i < arr_size; i++)
	{
		if (arr[i] < arr[min_index])
			min_index = i;
		if (non_negative && arr[i] == 0)
			return i;
	}
	return min_index;
}
void print_array(int* arr, int arr_size)
{
	for (int i = 0; i < arr_size; i++)
		printf("%d\t", arr[i]);
	printf("\n");
}