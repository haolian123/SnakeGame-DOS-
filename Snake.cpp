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
		//让蛇动起来
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
		//判断当前方向，根据Dir来移动
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
			cout << "游戏结束！" << endl;
			Go(Wid / 2 - 5, Len / 2+1);
			cout << "您的分数是：" << Score;
			Go(Wid / 2 - 5, Len / 2 + 2);
			return;
		
		}
		snake.front().Image = '+';
		snake.push_front(Tmp1);
		PrintSnake();
		Sleep(Speed + 30);
		//判断是否吃到食物
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
//打印地图
void SnakeGame::CreatMap()
{
	for (int i = 0; i != Wid; i += 2)
	{
		Go(i, 0);
		cout << "■";
	}
	for (int i = 0; i != Len; i += 1)
	{
		Go(Wid, i);
		cout << "■";
	}
	for (int i = 0; i != Len; i += 1)
	{
		Go(0,i);
		cout << "■";
	}
	for (int i =0; i != Wid+2; i += 2)
	{
		Go(i, Len);
		cout << "■";
	}
}
//生成食物
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

//生成蛇身
void SnakeGame::CreatSnake()
{
	snake.push_front ({ '#',Wid / 2,Len / 2 });
	for (int i = 0; i < 2; i++)
		snake.push_back({ '+',static_cast<short>(Wid / 2 + i + 1),Len / 2 });
	//初始化蛇身
}
//判断食物是否在蛇身
bool SnakeGame::JudgeIsFoodOnSnake()
{
	for (Snake S : snake)
	{
		if (S.x == FoodX && S.y == FoodY)
			return true;
	}
	return false;
}

//游戏结束条件
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
//监控用户键盘输入
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
//获取坐标
void SnakeGame::Go(short x, short y)
{	
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Pos = { x,y };
	SetConsoleCursorPosition(hOut, Pos);//移动光标
}
//吃到食物的情况
void SnakeGame::EatenFood()
{
	CreatFood();
	IsEatFood = true;
	Speed *= 0.9;
	Score+=5;
}
//打印蛇身
void SnakeGame::PrintSnake()
{
	auto it = snake.begin();
	for (; it<=snake.begin()+1&&it <= snake.end(); it++)//这里要注意
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
	cout << "贪吃蛇" << endl;
	Go(COL, i++);
	cout << "作者：huanghaolian" << endl;
	//cout << "按下任意键开始游戏" << endl;
	Go(COL, i++);
	system("pause");
	system("cls");
	i = 15;
	Go(COL, i++);
	cout << "请选择地图大小：";
	Go(COL, i++);
	cout << "1、小";
	Go(COL, i++);
	cout << "2、中";
	Go(COL, i++);
	cout << "3、大";
	int select = 0;
	Go(COL, i++);
	cin >> select;
	return select;

}
void SnakeGame::Intruduce()
{
	Go(Wid + 16, Len / 2);
	cout << " 按w s a d控制方向 ";
	Go(Wid + 17, Len / 2+2);
	cout << "碰到墙壁或蛇的身体则游戏结束！";
}
void SnakeGame::ShowScore()
{
	Go(Wid + 20, Len / 2 + 4);
	cout << "当前的分数：" << Score;
}