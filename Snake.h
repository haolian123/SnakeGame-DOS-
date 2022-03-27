#pragma once
#include<iostream>
#include<deque>
#include<Windows.h>
#include<ctime>
#include<conio.h>
using namespace std;
class SnakeGame
{
public:
	struct Snake
	{
		char Image;//蛇的图案
		short x, y;//坐标
	};
	SnakeGame();

	~SnakeGame();

	//打印地图
	void CreatMap();

	//生成食物
	void CreatFood();

	//生成蛇身
	void CreatSnake();

	//打印蛇身
	void PrintSnake();

	//清除蛇尾
	void CleanTail(Snake &Tail);

	//判断食物是否在蛇身
	bool JudgeIsFoodOnSnake();

	//游戏结束条件
	bool JudgeIsDead();

	//判断是否键入
	void UserInput();

	//获取坐标
	void Go(short x, short y);

	//如果吃到食物
	void EatenFood();

	//开始游戏
	void StartGame();

	//隐藏光标
	void HideCursor();

	//主菜单
	int ShowMenu();
	//操作说明
	void Intruduce();
	//显示分数
	void ShowScore();
	//地图的大小
	short Wid, Len;
private:
	
	HANDLE hOut;
	COORD Pos;
	bool IsEatFood, Beg;
	double Speed;
	
	deque<Snake>snake;
	int FoodX, FoodY;
	int Score;
	char Dir;//方向
};