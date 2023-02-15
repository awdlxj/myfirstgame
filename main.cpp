#include <iostream>
#include <ctime>
#include <string>
#include "timer.h"
#include <Windows.h>
#include <math.h>
using namespace std;
timer t;


bool cls() //编程方式实现清除屏幕，防止屏幕闪烁
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };    /* here's where we'll home the cursor */
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
	DWORD dwConSize;                 /* number of character cells in the current buffer */

	//CONSOLE_CURSOR_INFO CursorInfo;
	//GetConsoleCursorInfo(hConsole, &CursorInfo);//获取控制台光标信息
	//CursorInfo.bVisible = false; //隐藏控制台光标
	//SetConsoleCursorInfo(hConsole, &CursorInfo);//设置控制台光标状态

	/* get the number of character cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return false;
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	/* fill the entire screen with blanks */
	if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten))
		return false;

	/* get the current text attribute */
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return false;

	/* now set the buffer's attributes accordingly */
	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten))
		return false;

	/* put the cursor at (0, 0) */
	if (!SetConsoleCursorPosition(hConsole, coordScreen))
		return false;
}

int main()
{
	t.gettimerfreq();
	string lefts, rights,all1,all2;
	double fps = 0, sinx = 0,high=0,low=99999;
	while (1)
	{
		fps = 1 / t.endtimer();
		if (high < fps && fps > 0)
			high = fps;
		if (low > fps && fps > 0)
			low = fps;
		t.starttimer();
		cls();

		all1 = "FPS:" + to_string(fps) + "\tHIGH:" + to_string(high) + "\tLOW:" + to_string(low) + "\n";
		cout << all1;
		

		sinx += 0.01;
		int x = sin(sinx)*51;
		lefts = "";
		for (int i = 0; i < x/2+25; i++)
		{
			lefts += "|";
		}
		rights = "";

		for (int i = 0; i < 50- x / 2 - 25; i++)
		{
			rights += "=";
		}
		all2 = lefts + rights + " " + to_string(sin(sinx));
		cout << all2;


		Sleep(2);
	}
}