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
		char Image;//�ߵ�ͼ��
		short x, y;//����
	};
	SnakeGame();

	~SnakeGame();

	//��ӡ��ͼ
	void CreatMap();

	//����ʳ��
	void CreatFood();

	//��������
	void CreatSnake();

	//��ӡ����
	void PrintSnake();

	//�����β
	void CleanTail(Snake &Tail);

	//�ж�ʳ���Ƿ�������
	bool JudgeIsFoodOnSnake();

	//��Ϸ��������
	bool JudgeIsDead();

	//�ж��Ƿ����
	void UserInput();

	//��ȡ����
	void Go(short x, short y);

	//����Ե�ʳ��
	void EatenFood();

	//��ʼ��Ϸ
	void StartGame();

	//���ع��
	void HideCursor();

	//���˵�
	int ShowMenu();
	//����˵��
	void Intruduce();
	//��ʾ����
	void ShowScore();
	//��ͼ�Ĵ�С
	short Wid, Len;
private:
	
	HANDLE hOut;
	COORD Pos;
	bool IsEatFood, Beg;
	double Speed;
	
	deque<Snake>snake;
	int FoodX, FoodY;
	int Score;
	char Dir;//����
};