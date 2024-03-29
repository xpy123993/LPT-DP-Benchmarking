// DP_LPT_P2COMMONDUEDATE.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "job.h"
#include "p_algorithm.h"
#include "dp_utils.h"
#include <Windows.h>

void solve_problem_using_LPT(TaskInfo& taskInfo)
{
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceCounter(&t1);
	int result = lpt_solve(taskInfo);
	QueryPerformanceCounter(&t2);
	QueryPerformanceFrequency(&tc);
	double running_time = (t2.QuadPart - t1.QuadPart) / (tc.QuadPart);
	printf("LPT Schedule\nResult = %d, Running time: %.5f\n", result, running_time);
}

void solve_problem_using_DP(TaskInfo& taskInfo)
{
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceCounter(&t1);
	int result = dp_solve(taskInfo);
	QueryPerformanceCounter(&t2);
	QueryPerformanceFrequency(&tc);
	double running_time = 1.0 * (t2.QuadPart - t1.QuadPart) / (tc.QuadPart);
	printf("DP Algorithm\nResult = %d, Running time: %lf\n", result, running_time);
}


void taskInfo_test()
{
	/*
	proc in (5, 100)
	due date = total proc / machine num
	*/
	TaskInfo problem = task_generate(14, 3);
	dump_taskInfo(problem);

	solve_problem_using_DP(problem);
	solve_problem_using_LPT(problem);
}

int main()
{
	srand(time(0));

	taskInfo_test();

	printf("Algorithm finished. Press [Enter] to exit.");
	getchar();
    return 0;
}

