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
		int x, y; //����
	};
	SnakeGame();
	void PrintMap();//���ƹ���ƶ�
	void GoXY(short x, short y);//�ƶ����
	void HideCursor();//���ع��
	void InitSnake();//��ʼ������
	bool WrongLocation();//�����Ƿ���ʳ�����λ�ó�ͻ
	void CreateFood();//�������ʳ��
	void PrintSnake();
	void ClearSnake(Snake& tail);
	void JudgeCrash();//�Ƿ���
	void FoodEaten();
	void UserInput();//����û���������
private:
	enum MapSize { Height = 40, Width = 120 };
	HANDLE hOut;
	COORD pos;
	char Dir;//����
	bool Beg, EatFood;
	double Speed;
	deque<Snake>snake;
	int Food_X, Food_Y;
	int Score;
};