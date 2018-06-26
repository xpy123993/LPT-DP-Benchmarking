#pragma once

#include "stdafx.h"
#include "helper.h"

const int MIN_PROCESS_TIME = 5;
const int MAX_PROCESS_TIME = 100;

struct TaskInfo
{
	int due_date;
	int job_procs[1000], total_proc;
	int n, m;
};

TaskInfo task_generate(int n, int m)
{
	printf("Generating problems: n = %d, m = %d\n", n, m);
	TaskInfo taskInfo;

	taskInfo.n = n;
	taskInfo.m = m;
	taskInfo.total_proc = 0;

	for (int i = 0; i < n; i++)
	{
		taskInfo.job_procs[i] = randint(MIN_PROCESS_TIME, MAX_PROCESS_TIME);
		taskInfo.total_proc += taskInfo.job_procs[i];
	}
	taskInfo.due_date = (int) (1.0 * taskInfo.total_proc / m);

	return taskInfo;
}

void dump_taskInfo(TaskInfo& taskInfo)
{
	printf("Task Details\n");
	printf("Job Num: %d, Machine Num: %d\n", taskInfo.n, taskInfo.m);
	printf("Job Process time:\n");
	for (int i = 0; i < taskInfo.n; i++)
	{
		if (i % 10 == 0 && i > 0) printf("\n");
		printf("%2d, ", taskInfo.job_procs[i]);
	}
	printf("\nTotal process time: %d, common due date: %d\n", taskInfo.total_proc, taskInfo.due_date);
}