// DP_LPT_P2COMMONDUEDATE.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "job.h"
// 问题描述、生成

/*

proc in (5, 100)
due date = total proc / machine num

*/

void taskInfo_test()
{
	TaskInfo problem = task_generate(10, 3);
	dump_taskInfo(problem);
}

int main()
{
	taskInfo_test();

	getchar();
    return 0;
}

