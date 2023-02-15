#include "timer.h"

#include <windows.h>

#include <iostream>

using namespace std;

double timer::gettimerfreq()//���ʱ������Ƶ�ʣ�����ִ������һ��
{
	LARGE_INTEGER   litmp;
	QueryPerformanceFrequency(&litmp);
	timerfreq = (double)litmp.QuadPart;//   ��ü�������ʱ��Ƶ��
	return timerfreq;
}

bool timer::starttimer() //��ʼ��ʱ���ɹ�����1��ʧ�ܷ���0��ʧ��ԭ������ִ��һ��gettimerfreq��
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
double timer::getthroughtime()//ȡ����ʱ����ʱ�䣬��λ��s���ɹ�����˫����ʱ�䣬ʧ�ܷ���һ��������ʧ��ԭ������ִ��һ��gettimerfreq��δ��ʼ��ʱ
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
		QPart = litmp.QuadPart;//�����ֵֹ
		dfMinus = (double)(QPart - this->startcycle);
		dfTim = dfMinus / timerfreq;//   �����Ӧ��ʱ��ֵ����λΪ��
		return dfTim;
	}
}
double timer::endtimer()//ȡ����ʱ����ʱ�䲢������ʱ����λ��s���ɹ�����˫����ʱ�䣬ʧ�ܷ���һ��������ʧ��ԭ������ִ��һ��gettimerfreq��δ��ʼ��ʱ
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
		QPart = litmp.QuadPart;//�����ֵֹ
		dfMinus = (double)(QPart - this->startcycle);
		dfTim = dfMinus / timerfreq;//   �����Ӧ��ʱ��ֵ����λΪ��
		this->startcycle = -99999;
		return dfTim;
	}
}
timer::timer()
{
	timerfreq = -99999;
	this->startcycle = -99999;
}