#pragma warning (disable:4996)
#include<iostream>
#include"Snake.h"
using namespace std;
int main()
{
	while (1)
	{
		
		system("mode con cols=100 lines=40");
		SnakeGame S;
		
		int Select=S.ShowMenu();
		switch (Select)
		{
		case 1:
			S.Len = 20, S.Wid = 40; 
			system("mode con cols=100 lines=30"); break;
		case 2:
			S.Len = 30, S.Wid = 60; 
			system("mode con cols=120 lines=40"); break;
		case 3:
			S.Len = 40, S.Wid = 100; 
			system("mode con cols=180 lines=60"); break;
		}
		system("cls");
		S.StartGame();
		cout << "请选择：";
		S.Go(S.Wid / 2 - 5, S.Len / 2 + 3);
		cout << "1、重新开始";
		S.Go(S.Wid / 2 - 5, S.Len / 2 + 4);
		cout << "2、退出游戏";
		S.Go(S.Wid / 2 - 5, S.Len / 2 + 5);
		int select = 0;
		cin >> select;
		if (select == 2)
		{
			S.Go(S.Wid / 2 - 5, S.Len / 2 + 6);
			cout << "欢迎下次使用！" << endl;
			S.Go(0, S.Len + 5);
			return 0;
		}
	}
	
}