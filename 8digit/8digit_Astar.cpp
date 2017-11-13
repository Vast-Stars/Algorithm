#include "stdafx.h"
#include <iostream>
#include<vector>
#include <iomanip>
#include<algorithm>
// The Side length of Matrix;  SIZE=n means (n*n-1)digit problem.
#define SIZE 3 
using namespace std;
struct status;
vector<status> Open, Close;
int  TARGET[SIZE*SIZE] = { 0 };

void generate_Target()
{
	int count, i, j, k, kend, lend;
	kend = SIZE / 2;
	lend = SIZE;
	count = 1;
	for (i = 0, j = 0, k = 0; k<kend; k++)
	{
		TARGET[SIZE*i+j] = count++;

		for (j++; j<lend; j++)
			TARGET[SIZE*i + j] = count++;

		for (i++, j--; i<lend; i++)
			TARGET[SIZE*i + j] = count++;

		for (i--, j--; j >= k; j--)
			TARGET[SIZE*i + j] = count++;

		for (i--, j++; i>k; i--)
			TARGET[SIZE*i + j] = count++;

		i++; j++; lend--;
	}

	if (SIZE % 2 != 0) TARGET[i*SIZE+j] = 0;

	for (i = 0; i<SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
			cout << TARGET[i*SIZE+j];
		cout << endl;
	}

}

int reverse_nums(int a[SIZE*SIZE])
{
	int counter=0;
	for (int i = 0; i < SIZE*SIZE; i++)
	{
		if (*(a + i) == 0)
			continue;
		for (int j = SIZE*SIZE-1; j >i; j--)
		{
			if (*(a + i) < *(a + j))
				counter++;
		}
	}
	return counter;
}
bool valid_case(int a[SIZE*SIZE], int b[SIZE*SIZE])
{
	return reverse_nums(a)%2==reverse_nums(b)%2?true:false;
}

int check(const int *p)
{
	int h = 0, i = 0;
	for (i = 0; i < SIZE*SIZE ; i++)
		if (*(p +i)!= *(TARGET+i))
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
	string path = " ";
	status()
	{
		memset(m, 0, sizeof(int) * SIZE*SIZE);
	}
	status(int *p)
	{
		memcpy(m, p, sizeof(int) * SIZE*SIZE);
	}
	bool operator< (const status &a)const
	{
		return a.F > F;  //由小到大排列  
	}
	void operator= (int *p)
	{
		memcpy(m, p, sizeof(int) * SIZE*SIZE);
	}
	void operator= (initializer_list<int> p)
	{
		copy(p.begin(), p.end(), m);
	}

	//bool operator== (const status &a)const
	//{
	//	return a.statu == statu;
	//}
	void update()
	{
		g = path.size();
		h = check(m);
		F = g + h;
		for (int i = 0; i < SIZE*SIZE; i++)
		{
			if (m[i] == 0)
			{
				x = i / SIZE;
				y = i%SIZE;
			}
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
		cout << setw(4)<< *(p + i);
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
		if (s.y ==SIZE-1 || s.path.back() == 'l')
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
		if (s.y == 0 || s.path.back() == 'r')
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
		if (s.x == SIZE - 1 || s.path.back() == 'u')
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


std::vector<status>::const_iterator Find( vector<status>& ss, const status& a)
{
	vector<status>::const_iterator p=ss.end() ;

	for (p = ss.begin(); p != ss.end(); p++)
	{
		if( memcmp(p->m, a.m, sizeof(a.m))==0)
			return p;
	}
	return p;
}

//vector<status>::iterator  Find(vector<status>& ss, const status& a)
//{
//	vector<status>::iterator p = ss.end();
//	if (!ss.empty())
//		for (p = ss.begin(); p != ss.end(); p++)
//			if (p->statu == a.statu)
//				return p;
//	return p;
//}
vector<status> Generate_Next(const status &a)
{
	vector<status> Nex;
	status tem;
	tem = Move(a, 'l');
	if (tem.x != -1)
		Nex.push_back(tem);
	tem = Move(a, 'r');
	if (tem.x != -1)
		Nex.push_back(tem);
	tem = Move(a, 'u');
	if (tem.x != -1)
		Nex.push_back(tem);
	tem = Move(a, 'd');
	if (tem.x != -1)
		Nex.push_back(tem);
	return Nex;
}
int fun()
{
	status tem;
	tem = *Open.begin();
	if (tem.h==0)
		return 1;
	Close.push_back(tem);
	vector<status> nex;
	nex = Generate_Next(tem);
	for (auto it = nex.begin(); it != nex.end(); it++)
	{
		if (Find(Close, *it) == Close.end())
		{
//	cout << it->statu << "  不在Close中!" << endl;
			vector<status>::const_iterator & tem3 = Find(Open, *it);
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
	generate_Target();
	status S,S1;
//S即为输入。假定为有解输入。
	//S = { 1,2,3,0,8,4,7,6,5};
	S = {7,5,3,1,6,4,2,8,0};
	S.update();

	if (!valid_case(S.m, TARGET))
	{
		cout << "Invalid input!" << endl;
		return 0;
    }

	Open.push_back(S);

	print((*Open.begin()).m);
	int step = 0;
	while (!fun())
	{
		sort(Open.begin(), Open.end());
		//printf("fun:%d:  Size of Open:%d\n", step++,Open.size());
//print((*Open.begin()).m);
	}
	status answer = *Open.begin();
	string path =answer.path;

	for (size_t i=1;i<path.size();i++)
	{
		S = Move(S, path[i]);
		print(S.m);
	}
	cout << "Length:" << path.size()-1;
	getchar();
	return 0;
}

