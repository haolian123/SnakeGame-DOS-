#include"Snake.h"
#pragma warning (disable:4996)
#define COL 30
SnakeGame::SnakeGame()
{
	Speed = 200;
	Score = 0;
	//FoodX = FoodY = 0;
	this->IsEatFood = false;
	srand((unsigned int)time(NULL));
	Beg = true;
	HideCursor();
}
void SnakeGame::StartGame()
{
	Snake Tmp1, Tmp2;
	while (1)
	{
		if (Beg)
		{
			CreatMap();
			
			CreatSnake();
			CreatFood();
			auto it = snake.begin();
			
			for (; it != snake.end(); it++)
			{
				Go(it->x, it->y);
				cout << it->Image;
			}
			Intruduce();
			ShowScore();
			Dir = getch();
			Beg = false;
		}
		//���߶�����
		Tmp2 = snake.back();
		Tmp1 = snake.front();
		snake.pop_back();
		
		if (IsEatFood)
		{
			IsEatFood = false;
			Tmp2.Image = '+';
			snake.push_back(Tmp2);
		}
		else { 
			CleanTail(Tmp2);
		};
		//�жϵ�ǰ���򣬸���Dir���ƶ�
		if (Dir == 's')
			++Tmp1.y;
		else if (Dir == 'a')
			--Tmp1.x;
		else if (Dir == 'd')
			++Tmp1.x;
		else if (Dir == 'w')
			--Tmp1.y;
		
		if (JudgeIsDead())
		{
			Go(Wid / 2 - 5, Len / 2);
			cout << "��Ϸ������" << endl;
			Go(Wid / 2 - 5, Len / 2+1);
			cout << "���ķ����ǣ�" << Score;
			Go(Wid / 2 - 5, Len / 2 + 2);
			return;
		
		}
		snake.front().Image = '+';
		snake.push_front(Tmp1);
		PrintSnake();
		Sleep(Speed + 30);
		//�ж��Ƿ�Ե�ʳ��
		if (Tmp1.x == FoodX && Tmp1.y == FoodY)
			EatenFood();
		ShowScore();
		if (kbhit())
			UserInput();
	}
}
SnakeGame::~SnakeGame()
{
	snake.clear();
}
//��ӡ��ͼ
void SnakeGame::CreatMap()
{
	for (int i = 0; i != Wid; i += 2)
	{
		Go(i, 0);
		cout << "��";
	}
	for (int i = 0; i != Len; i += 1)
	{
		Go(Wid, i);
		cout << "��";
	}
	for (int i = 0; i != Len; i += 1)
	{
		Go(0,i);
		cout << "��";
	}
	for (int i =0; i != Wid+2; i += 2)
	{
		Go(i, Len);
		cout << "��";
	}
}
//����ʳ��
void SnakeGame::CreatFood()
{
	while (1)
	{
		FoodX = rand() % (Wid-4)+2;
		FoodY = rand() % (Len-2)+1;
		if (JudgeIsFoodOnSnake())
			continue;
		else
		{
			
			Go(FoodX, FoodY);
			cout << "$";
			return;
		}
	}
}

//��������
void SnakeGame::CreatSnake()
{
	snake.push_front ({ '#',Wid / 2,Len / 2 });
	for (int i = 0; i < 2; i++)
		snake.push_back({ '+',static_cast<short>(Wid / 2 + i + 1),Len / 2 });
	//��ʼ������
}
//�ж�ʳ���Ƿ�������
bool SnakeGame::JudgeIsFoodOnSnake()
{
	for (Snake S : snake)
	{
		if (S.x == FoodX && S.y == FoodY)
			return true;
	}
	return false;
}

//��Ϸ��������
bool SnakeGame::JudgeIsDead()
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
	deque<Snake>::iterator head = snake.begin();
	if ( head->x == 1 || head->y == 0 || head->y == Len  || head->x == Wid )
	{
		flag = true;
	}
	return flag;
}
//����û���������
void SnakeGame::UserInput()
{
	char Ch;
	switch (Ch = getch())
	{
	case'w':
		if (Dir != 's')
			Dir = Ch; break;
	case 's':
		if (Dir != 'w')
			Dir = Ch; break;
	case 'a':
		if (Dir != 'd')
			Dir = Ch; break;
	case 'd':
		if (Dir != 'a')
			Dir = Ch; break;
	}
	
}
//��ȡ����
void SnakeGame::Go(short x, short y)
{	
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Pos = { x,y };
	SetConsoleCursorPosition(hOut, Pos);//�ƶ����
}
//�Ե�ʳ������
void SnakeGame::EatenFood()
{
	CreatFood();
	IsEatFood = true;
	Speed *= 0.9;
	Score+=5;
}
//��ӡ����
void SnakeGame::PrintSnake()
{
	auto it = snake.begin();
	for (; it<=snake.begin()+1&&it <= snake.end(); it++)//����Ҫע��
	{
		Go(it->x, it->y);
		cout << it->Image;
	}
}
void SnakeGame::CleanTail( Snake &Tail)
{
	Go(Tail.x, Tail.y);
	cout << ' ';
}
void SnakeGame::HideCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO Cursorinfo;
	GetConsoleCursorInfo(handle, &Cursorinfo);
	Cursorinfo.bVisible = false;
	SetConsoleCursorInfo(handle, &Cursorinfo);
}
int SnakeGame::ShowMenu()
{
	int i = 15;
	Go(COL+5,i++);
	cout << "̰����" << endl;
	Go(COL, i++);
	cout << "���ߣ�huanghaolian" << endl;
	//cout << "�����������ʼ��Ϸ" << endl;
	Go(COL, i++);
	system("pause");
	system("cls");
	i = 15;
	Go(COL, i++);
	cout << "��ѡ���ͼ��С��";
	Go(COL, i++);
	cout << "1��С";
	Go(COL, i++);
	cout << "2����";
	Go(COL, i++);
	cout << "3����";
	int select = 0;
	Go(COL, i++);
	cin >> select;
	return select;

}
void SnakeGame::Intruduce()
{
	Go(Wid + 16, Len / 2);
	cout << " ��w s a d���Ʒ��� ";
	Go(Wid + 17, Len / 2+2);
	cout << "����ǽ�ڻ��ߵ���������Ϸ������";
}
void SnakeGame::ShowScore()
{
	Go(Wid + 20, Len / 2 + 4);
	cout << "��ǰ�ķ�����" << Score;
}