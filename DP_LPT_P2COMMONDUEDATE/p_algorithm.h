#pragma once

/*
This file contains two algorithms

1. LPT List schedule
2. DP schedule

LPT Schedule

ratio = nm / ((n - 1)m + 1)

*/

#include "stdafx.h"
#include "helper.h"
#include "job.h"
#include "dp_utils.h"

#include <windows.h>

inline double _lpt_solve_ratio(int n, int m) { return 1.0 * m * n / ((n - 1) * m + 1); }

int _LPT_COMPLETION_TIME[MAX_M], _DP_TABLE_INDEX[MAX_M + 1];

double lpt_running_time, dp_running_time;

int lpt_solve(TaskInfo& taskInfo)
{
	int machine_id = 0;
	double ratio = _lpt_solve_ratio(taskInfo.n, taskInfo.m);

	memset(_LPT_COMPLETION_TIME, 0, sizeof(int) * taskInfo.m);
	sort(taskInfo.job_procs, taskInfo.job_procs + taskInfo.n, [](int a, int b) { return a > b; });

	for (int i = 0; i < taskInfo.n; i++)
	{
		machine_id = argmin(_LPT_COMPLETION_TIME, taskInfo.m, true);
		_LPT_COMPLETION_TIME[machine_id] += taskInfo.job_procs[i];
	}

	int early_work = 0;
	for (int i = 0; i < taskInfo.m; i++)
		early_work += min(taskInfo.due_date, (int)(ratio * _LPT_COMPLETION_TIME[i]));

	return taskInfo.total_proc - early_work;
}

void _dp_recursive_fill_table(int deep, TaskInfo& taskInfo, DP_table& table, int job_id, int job_proc_time)
{
	if (taskInfo.m == deep)
	{
		int temp_index, backup_early_work, resi_result, min_val = 10000007;
		for (int machine_id = 0; machine_id < taskInfo.m; machine_id++)
		{
			resi_result = max(job_proc_time - _DP_TABLE_INDEX[machine_id], 0);

			if (job_id > 0)
			{
				temp_index = max(0, _DP_TABLE_INDEX[machine_id] - job_proc_time);
				backup_early_work = _DP_TABLE_INDEX[machine_id];
				_DP_TABLE_INDEX[machine_id + 1] = temp_index;
				_DP_TABLE_INDEX[0] -= 1;

				resi_result += table.val(_DP_TABLE_INDEX);

				_DP_TABLE_INDEX[0] += 1;
				_DP_TABLE_INDEX[machine_id + 1] = backup_early_work;
			}

			min_val = min(min_val, resi_result);
		}
		table.set_val(_DP_TABLE_INDEX, min_val);

	}
	else
	{
		for (int i = 0; i <= taskInfo.due_date; i++)
		{
			_DP_TABLE_INDEX[deep + 1] = i;
			_dp_recursive_fill_table(deep + 1, taskInfo, table, job_id, job_proc_time);
		}
	}
}

int dp_solve(TaskInfo& taskInfo)
{
	DP_table table(taskInfo.n, taskInfo.m, taskInfo.due_date);

	for (int i = 0; i < taskInfo.n; i++)
	{
		_DP_TABLE_INDEX[0] = i;
		_dp_recursive_fill_table(0, taskInfo, table, i, taskInfo.job_procs[i]);
	}
	
	_DP_TABLE_INDEX[0] = taskInfo.n - 1;
	for (int i = 0; i < taskInfo.m; i++)
		_DP_TABLE_INDEX[i + 1] = taskInfo.due_date;

	return table.val(_DP_TABLE_INDEX);
}
