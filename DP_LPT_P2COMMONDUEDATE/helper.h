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