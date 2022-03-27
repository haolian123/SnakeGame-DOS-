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
		if (Beg)// 判断是不是第一次运行程序，因为第一次运行需要打印边框
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
		//判断当前的前进方向，根据Dir来进行移动
		if (Dir == 's')
			++Tmp1.y;
		else if (Dir == 'a')
			--Tmp1.x;
		else if (Dir == 'd')
			++Tmp1.x;
		else if (Dir == 'w')
			--Tmp1.y;
		try {
			JudgeCrash(); // 判断是否撞墙或者吃到自己
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
		//监测用户的键入
		if (kbhit())
			UserInput();
	}
}
void  SnakeGame::PrintMap()//控制光标移动
{
	int i;
	for (i = 0; i != Width; i += 2)
		cout << "■"; //这个图案宽度占2，高度占1
	GoXY(0, 1);
	for (i = 1; i != Height; i++)
		cout << "■" << endl;
	for (int i = 1; i != Height; ++i)
	{
		GoXY(Width - 2, i);
		cout << "■";
	}
	GoXY(0, Height - 1);
	for (int i = 0; i != Width; i += 2)
		cout << "■";
	cout << "贪吃蛇：1.方向键开始游戏 2.*代表食物 3.空格键暂停游戏" << endl;
}
void  SnakeGame::GoXY(short x, short y)
{
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	pos = { x,y };
	SetConsoleCursorPosition(hOut, pos);//移动光标
}//移动光标
void  SnakeGame::HideCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false;//隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
}//隐藏光标
void  SnakeGame::InitSnake()
{
	snake.push_front({ '#',Width / 2,Height / 2 });
	for (int i = 0; i < 2; i++)
		snake.push_back({ '#',Width / 2,static_cast<short>(Height / 2 + i + 1) });
}//初始化蛇身,课根据需要更改初始化长度
bool  SnakeGame::WrongLocation()
{
	for (Snake body : snake)//*快速遍历容器
	{
		if (body.x == Food_X && body.y == Food_Y)
			return true;
		
	}
	return false;
}//蛇身是否与食物出现位置冲突
void  SnakeGame::CreateFood()
{
	do
	{
		Food_X = rand() % (Width - 4) + 2;
		Food_Y = rand() % (Height - 2) + 1;
	} while (WrongLocation());
	GoXY(Food_X, Food_Y);
	cout << '$' << endl;
}//随机产生食物
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
		//检测是否撞墙或者是否吃到自身
	{
		GoXY(Width / 2 - 10, Height / 2);
		cout << "游戏结束！您的分数是：" << Score << "分(按回车继续)" << endl;
		while (1)
		{
			Dir = getch();
			if (Dir == '\r')
				break;
		}
		runtime_error quit("游戏结束，正常退出"); throw quit;//***
	}
}// 判断蛇是否撞墙或者吃到自己的尾巴
void  SnakeGame::FoodEaten()// 处理吃到食物的情况
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
	case ' ':GoXY(Width / 2, Height); cout << "游戏已暂停，";
		system("pause");
		GoXY(Width / 2, Height); cout << "                               "; break;
	}
}//监控用户键盘输入