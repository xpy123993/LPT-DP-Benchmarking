// DP_LPT_P2COMMONDUEDATE.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "job.h"
#include "p_algorithm.h"
#include "dp_utils.h"

void taskInfo_test()
{
	/*
	proc in (5, 100)
	due date = total proc / machine num
	*/
	TaskInfo problem = task_generate(20, 3);
	dump_taskInfo(problem);

	printf("LPT RESULT = %d\n", lpt_solve(problem));
	printf("DP RESULT = %d\n", dp_solve(problem));
}

int main()
{
	taskInfo_test();

	printf("Algorithm finished. Press [Enter] to exit.");
	getchar();
    return 0;
}

