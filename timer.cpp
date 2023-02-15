#include "timer.h"

#include <windows.h>

#include <iostream>

using namespace std;

double timer::gettimerfreq()//获得时钟周期频率，必须执行至少一次
{
	LARGE_INTEGER   litmp;
	QueryPerformanceFrequency(&litmp);
	timerfreq = (double)litmp.QuadPart;//   获得计数器的时钟频率
	return timerfreq;
}

bool timer::starttimer() //开始计时，成功返回1，失败返回0。失败原因：至少执行一次gettimerfreq。
{

	if (timerfreq < 0)
	{
		return 0;
	}
	else
	{
		LARGE_INTEGER  litmp;
		QueryPerformanceCounter(&litmp);
		this->startcycle = litmp.QuadPart;
		return 1;
	}
}
double timer::getthroughtime()//取出计时经历时间，单位：s，成功返回双精度时间，失败返回一个负数。失败原因：至少执行一次gettimerfreq或并未开始计时
{
	if (timerfreq < 0)
	{
		return -1.0;
	}
	else if (this->startcycle < 0)
	{
		return -1.0;
	}
	else
	{
		LARGE_INTEGER   litmp;
		long long   QPart;
		double   dfMinus, dfTim;
		QueryPerformanceCounter(&litmp);
		QPart = litmp.QuadPart;//获得中止值
		dfMinus = (double)(QPart - this->startcycle);
		dfTim = dfMinus / timerfreq;//   计算对应的时间值，单位为秒
		return dfTim;
	}
}
double timer::endtimer()//取出计时经历时间并结束计时，单位：s，成功返回双精度时间，失败返回一个负数。失败原因：至少执行一次gettimerfreq或并未开始计时
{
	if (timerfreq < 0)
	{
		return -1.0;
	}
	else if (this->startcycle < 0)
	{
		return -1.0;
	}
	else
	{
		LARGE_INTEGER   litmp;
		long long   QPart;
		double   dfMinus, dfTim;
		QueryPerformanceCounter(&litmp);
		QPart = litmp.QuadPart;//获得中止值
		dfMinus = (double)(QPart - this->startcycle);
		dfTim = dfMinus / timerfreq;//   计算对应的时间值，单位为秒
		this->startcycle = -99999;
		return dfTim;
	}
}
timer::timer()
{
	timerfreq = -99999;
	this->startcycle = -99999;
}