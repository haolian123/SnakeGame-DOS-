#pragma warning (disable:4996)
#include"Snake.h"
#include<iostream>
using namespace std;
int main()
{
	system("mode con cols=120 lines=42");
	try
	{
		SnakeGame G;
	}
	catch (runtime_error& GameEnd)
	{
		system("cls");
		cout << GameEnd.what();
		getch();
	}

}