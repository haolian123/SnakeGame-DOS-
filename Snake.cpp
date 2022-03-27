#include"Snake.h"
SnakeGame::SnakeGame()
{
	Speed = 200;
	Score = 0;
	Beg = EatFood = false;
	HideCursor();
	srand((unsigned int)time(NULL));
	Beg = true;
	Snake Tmp1, Tmp2;
	while (1)
	{
		if (Beg)// �ж��ǲ��ǵ�һ�����г�����Ϊ��һ��������Ҫ��ӡ�߿�
		{
			PrintMap();
			Dir = getch();
			InitSnake();
			CreateFood();
			Beg = EatFood = false;
		}
		Tmp2 = snake.back();
		Tmp1 = snake.front();
		snake.pop_back();//**
		if (EatFood)
		{
			Tmp2.image = '+';
			snake.push_back(Tmp2);
			EatFood = false;
		}
		else ClearSnake(Tmp2);
		//�жϵ�ǰ��ǰ�����򣬸���Dir�������ƶ�
		if (Dir == 's')
			++Tmp1.y;
		else if (Dir == 'a')
			--Tmp1.x;
		else if (Dir == 'd')
			++Tmp1.x;
		else if (Dir == 'w')
			--Tmp1.y;
		try {
			JudgeCrash(); // �ж��Ƿ�ײǽ���߳Ե��Լ�
		}
		catch (runtime_error& quitSignal) {
			throw quitSignal;
		}
		snake.front().image = '+';
		snake.push_front(Tmp1);
		PrintSnake();
		Sleep(Speed + 30);
		if (Tmp1.x == Food_X && Tmp1.y == Food_Y)
			FoodEaten();
		//����û��ļ���
		if (kbhit())
			UserInput();
	}
}
void  SnakeGame::PrintMap()//���ƹ���ƶ�
{
	int i;
	for (i = 0; i != Width; i += 2)
		cout << "��"; //���ͼ�����ռ2���߶�ռ1
	GoXY(0, 1);
	for (i = 1; i != Height; i++)
		cout << "��" << endl;
	for (int i = 1; i != Height; ++i)
	{
		GoXY(Width - 2, i);
		cout << "��";
	}
	GoXY(0, Height - 1);
	for (int i = 0; i != Width; i += 2)
		cout << "��";
	cout << "̰���ߣ�1.�������ʼ��Ϸ 2.*����ʳ�� 3.�ո����ͣ��Ϸ" << endl;
}
void  SnakeGame::GoXY(short x, short y)
{
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	pos = { x,y };
	SetConsoleCursorPosition(hOut, pos);//�ƶ����
}//�ƶ����
void  SnakeGame::HideCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false;//���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
}//���ع��
void  SnakeGame::InitSnake()
{
	snake.push_front({ '#',Width / 2,Height / 2 });
	for (int i = 0; i < 2; i++)
		snake.push_back({ '#',Width / 2,static_cast<short>(Height / 2 + i + 1) });
}//��ʼ������,�θ�����Ҫ���ĳ�ʼ������
bool  SnakeGame::WrongLocation()
{
	for (Snake body : snake)//*���ٱ�������
	{
		if (body.x == Food_X && body.y == Food_Y)
			return true;
		
	}
	return false;
}//�����Ƿ���ʳ�����λ�ó�ͻ
void  SnakeGame::CreateFood()
{
	do
	{
		Food_X = rand() % (Width - 4) + 2;
		Food_Y = rand() % (Height - 2) + 1;
	} while (WrongLocation());
	GoXY(Food_X, Food_Y);
	cout << '$' << endl;
}//�������ʳ��
void  SnakeGame::PrintSnake()
{
	auto it = snake.begin();
	for (; it <= snake.begin() + 1 && it < snake.end(); it++)
	{
		GoXY(it->x, it->y);
		cout << it->image;
	}
}
void  SnakeGame::ClearSnake(Snake& tail)
{
	GoXY(tail.x, tail.y);
	cout << ' ';
}
void  SnakeGame::JudgeCrash()
{
	bool flag = false;
	if (snake.size() >= 5)
	{
		deque<Snake>::iterator it = snake.begin() + 1;
		int x = (it - 1)->x, y = (it - 1)->y;
		for (; it != snake.end(); it++)
		{
			if (it->x == x && it->y == y)
				flag = true;
		}

	}
	if (flag || snake.front().x == 1 || snake.front().x == Width - 2 ||
		snake.front().y == 0 || snake.front().y == Height - 1)
		//����Ƿ�ײǽ�����Ƿ�Ե�����
	{
		GoXY(Width / 2 - 10, Height / 2);
		cout << "��Ϸ���������ķ����ǣ�" << Score << "��(���س�����)" << endl;
		while (1)
		{
			Dir = getch();
			if (Dir == '\r')
				break;
		}
		runtime_error quit("��Ϸ�����������˳�"); throw quit;//***
	}
}// �ж����Ƿ�ײǽ���߳Ե��Լ���β��
void  SnakeGame::FoodEaten()// ����Ե�ʳ������
{
	CreateFood();
	EatFood = true;
	Speed *= .8;
	++Score;
}
void  SnakeGame::UserInput()
{
	char ch;
	switch (ch = getch())
	{
	case 'w':if (Dir != 's') Dir = ch; break;
	case 'a':if (Dir != 'd') Dir = ch; break;
	case 's':if (Dir != 'w') Dir = ch; break;
	case 'd':if (Dir != 'a') Dir = ch; break;
	case ' ':GoXY(Width / 2, Height); cout << "��Ϸ����ͣ��";
		system("pause");
		GoXY(Width / 2, Height); cout << "                               "; break;
	}
}//����û���������