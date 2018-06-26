#pragma once

#include "stdafx.h"

void* allocate_multidimension_array(int dim_size, int dim_num)
{
	if (dim_num == 1)
	{
		void* pointer = new int[dim_size];
		memset(pointer, 0, sizeof(int) * dim_size);
		return pointer;
	}
	void** pointer = new void*[dim_size];
	for (int i = 0; i < dim_size; i++)
	{
		pointer[i] = allocate_multidimension_array(dim_size, dim_num - 1);
	}
	return pointer;
}

void free_multidimension_array(int dim_size, int dim_num, void** pointer)
{
	if (dim_num > 1)
	{
		for (int i = 0; i < dim_size; i++)
		{
			free_multidimension_array(dim_size, dim_num - 1, (void**)pointer[i]);
		}
	}
	if (dim_num == 1)
		delete[]((int*)pointer);
	else
		delete[] pointer;

}

inline int& multidim_array_index(int* index, int index_count, void** table)
{
	for (int i = 0; i < index_count - 1; i++)
	{
		table = (void**)table[index[i]];
	}
	return ((int*)table)[index[index_count - 1]];
}

void free_dp_pn_table(void** table, int n, int m, int d)
{
	if (!table) return;
	for (int i = 0; i < n; i++)
	{
		free_multidimension_array(d + 1, m, (void**)table[i]);
	}
	delete[] table;
}

void** initialize_dp_pn_table(int n, int m, int d)
{
	void** table;
	table = new void*[n];
	for (int i = 0; i < n; i++)
	{
		table[i] = allocate_multidimension_array(d + 1, m);
	}
	return table;
}

class DP_table
{
	int n, m, d;
	void **table;

public:
	DP_table(int n, int m, int d): n(n), m(m), d(d)
	{
		table = initialize_dp_pn_table(n, m, d);
	}
	~DP_table()
	{
		free_dp_pn_table(table, n, m, d);
	}
	int val(int* index)
	{
		void** cur_table = table;
		for (int i = 0; i < m; i++)
		{
			cur_table = (void**)cur_table[index[i]];
		}
		return ((int*)cur_table)[index[m]];
	}
	void set_val(int* index, int val)
	{
		void** cur_table = table;
		for (int i = 0; i < m; i++)
		{
			cur_table = (void**)cur_table[index[i]];
		}
		((int*)cur_table)[index[m]] = val;
	}
};
