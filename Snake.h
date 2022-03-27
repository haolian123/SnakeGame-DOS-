#pragma once
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<deque>
#include<ctime>
#include<stdexcept>
#pragma warning (disable:4996)
using namespace std;

class SnakeGame
{
public:
	struct Snake
	{
		char image;
		int x, y; //坐标
	};
	SnakeGame();
	void PrintMap();//控制光标移动
	void GoXY(short x, short y);//移动光标
	void HideCursor();//隐藏光标
	void InitSnake();//初始化蛇身
	bool WrongLocation();//蛇身是否与食物出现位置冲突
	void CreateFood();//随机产生食物
	void PrintSnake();
	void ClearSnake(Snake& tail);
	void JudgeCrash();//是否输
	void FoodEaten();
	void UserInput();//监控用户键盘输入
private:
	enum MapSize { Height = 40, Width = 120 };
	HANDLE hOut;
	COORD pos;
	char Dir;//方向
	bool Beg, EatFood;
	double Speed;
	deque<Snake>snake;
	int Food_X, Food_Y;
	int Score;
};