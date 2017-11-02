/*
2017年9月27日
罗毅 15020520035
数据结构：status结构体。 m为数组矩阵。x y表示"0"的索引。 g h F负责计算“距离”。
statu为矩阵m的字符串表示，便于比较状态是否相同。path 记录从起始状态到当前状态走过的路径。
使用A* 算法。主要在于维护更新	Close、Open表 及 “距离”函数F的设定
*/
#include "stdafx.h"
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#define SIZE 3  
#define TARGET "123456780"

using namespace std;
struct status;
vector<status> Open, Close;
int check(const int *p)
{
	int h = 0, i = 0;
	for (i = 0; i < SIZE*SIZE - 1; i++)
		if (*(p +i)!= i + 1)
			h++;
	if (*(p+i) != 0)
		h++;
	return h;
}
struct status
{
	int m[SIZE*SIZE];
	int x, y;
	int g;
	int h;
	int F;
	string statu = " ";
	string path = " ";

	bool operator< (const status &a)const
	{
		return a.F > F;  //由小到大排列  
	}

	bool operator== (const status &a)const
	{
		return a.statu == statu;
	}
	bool operator!= (const status &a)const
	{
		return a.statu != statu;
	}
	bool equals(const status &a)const
	{
		return a.statu == statu;
	}

	void update()
	{
		char buffer[2];
		g = path.size();
		h = check(m);
		F = g + h;
		statu = " ";

		for (int i = 0; i < SIZE*SIZE; i++)
		{
			if (m[i] == 0)
			{
				x = i / SIZE;
				y = i%SIZE;
			}
			sprintf(buffer, "%d", m[i]);
			statu += buffer;
		}

	}
};



void print(const int *p)
//将字符串按矩阵形式输出
{
	int i = 0;
	cout << "Draw Matrix:" << endl;
	while (i < SIZE*SIZE)
	{
		cout << *(p + i) << ' ';
		if (++i % SIZE == 0)
			cout << endl;
	}
	cout << endl;

}

status  Move(status s, char direction)
//将空位沿指定方向移动得到新的状态。
//注意1：不能越界  2：防止自身嵌套，即不允许上一步右移之后再左移。
{
	int z_location = s.x*SIZE + s.y;
	status zero;
	zero.x = -1;
	switch (direction)
	{
	case 'r':
	{
		if (s.y%SIZE==SIZE-1 || s.path.back() == 'l')
			return zero ;
		else
		{
			s.m[z_location] = s.m[z_location + 1];
			s.m[z_location + 1] = 0;
			s.path += 'r';
		}
		break;
	}
	case 'l':
	{
		if (s.y%SIZE == 0 || s.path.back() == 'r')
			return zero;
		else
		{
			s.m[z_location] = s.m[z_location- 1];
			s.m[z_location - 1] = 0;
			s.path += 'l';
		}
		break;
	}
	case 'u':
	{
		if (s.x==0 || s.path.back() == 'd')
			return zero;
		else
		{
			s.m[z_location] = s.m[z_location -SIZE];
			s.m[z_location -SIZE] = 0;
			s.path += 'u';
		}
		break;
	}
	case 'd':
	{
		if (s.x/SIZE == SIZE - 1 || s.path.back() == 'u')
			return zero;
		else
		{
			s.m[z_location] = s.m[z_location+SIZE];
			s.m[z_location+SIZE] = 0;
			s.path += 'd';
		}
		break;
	}
	}
	s.update();
	return s;

}

 vector<status>::iterator  Find( vector<status>& ss, const status& a)
{
	 vector<status>::iterator p = ss.end();
	if(!ss.empty())
	for ( p = ss.begin(); p != ss.end(); p++)
		if (p->statu == a.statu)
			return p;
	return p;
}
int fun()
{
	status tem,tem2;
	tem = *Open.begin();
	
	if (tem.h==0)
		return 1;
	Close.push_back(tem);
	vector<status> nex;

	tem2 = Move(tem, 'l');
	if (tem2.x != -1)
		nex.push_back(tem2);
	tem2 = Move(tem, 'r');
	if (tem2.x != -1)
		nex.push_back(tem2);
	tem2 = Move(tem, 'u');
	if (tem2.x != -1)
		nex.push_back(tem2);
	tem2 = Move(tem, 'd');
	if (tem2.x != -1)
		nex.push_back(tem2);

	for (auto it = nex.begin(); it != nex.end(); it++)
	{
		if (Find(Close, *it) == Close.end())
		{
//			cout << it->statu << "  不在Close中!" << endl;
			vector<status>::iterator & tem3 = Find(Open, *it);
			if (tem3== Open.end())
			{
//				cout << it->statu << "  不在Open中!" << endl;
				Open.push_back(*it);
			}
			else if (tem3->F > it->F)
			{
				Open.erase(tem3);
				Open.push_back(*it);
			}
		}

	}
	nex.clear();
	Open.erase(Open.begin());
	return 0;
}
int main()
{
	status S;
//S即为输入。假定为有解输入。
	S = { 4,1,3,2,6,8,7,5,0 };
	S.update();
	Open.push_back(S);
	
	print((*Open.begin()).m);
	int step = 0;
	while (!fun())
	{
		sort(Open.begin(), Open.end());
		printf("fun:%d:  Size of Open:%d\n", step++,Open.size());
//print((*Open.begin()).m);
	}
	status answer = *Open.begin();
	string path =answer.path;

	for (int i=1;i<path.size();i++)
	{
		S = Move(S, path[i]);
		print(S.m);
	}
	getchar();
	return 0;
}

