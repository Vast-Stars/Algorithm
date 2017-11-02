/*2017年9月23日
罗毅  15020520035
数据结构： 3*3的九宫格可以用字符串表示，从左上角按行优先依次到右下角。0代表空位。例如目标状态可表示为"123405678"
字符串第10位开始记录当前移动的历史路径。避免调用过多堆栈。
广度优先算法。
*/
#include "stdafx.h"
#include <iostream>
#include <vector>
#include<queue>
#define  SIZE 3
using namespace std;


queue<string> Q;//用于储存待处理字符串的队列

void print(const string s)
//将字符串按矩阵形式输出
{
	int i = 0;
	cout << "Draw Matrix:" << endl;
	while (i < SIZE*SIZE)
	{
		cout << s[i] << ' ';
		if (++i % SIZE == 0)
			cout << endl;
	}
	cout << endl;

}

string Move(string s, char direction)
//将空位沿指定方向移动得到新的状态。
//注意1：不能越界  2：防止自身嵌套，即不允许上一步右移之后再左移。
{
	int tem = s.find('0');
	switch (direction)
	{
		case 'r': 
		{
			if (tem%SIZE == SIZE - 1 || s.back()=='l')
				return "";
			else
			{
				s[tem] = s[tem + 1];
				s[tem + 1] = '0';
				s += 'r';
			}
			break;
		}
		case 'l':
		{
			if (tem%SIZE == 0 || s.back() == 'r')
				return "";
			else
			{
				s[tem] = s[tem -1];
				s[tem - 1] = '0';
				s += 'l';
			}
			break;
		}
		case 'u':
		{
			if (tem/SIZE == 0 || s.back() == 'd')
				return "";
			else
			{
				s[tem] = s[tem -3];
				s[tem -3] = '0';
				s += 'u';
			}
			break;
		}
		case 'd':
		{
			if (tem/SIZE == SIZE-1 || s.back() == 'u')
				return "";
			else
			{
				s[tem] = s[tem + 3];
				s[tem +3] = '0';
				s += 'd';
			}
			break;
		}
	}
	return s;

}

int fun()
{
	string s,tem;
	s = Q.front();
	cout << s.c_str() <<" "<<Q.size()<< endl; //debug

	if (s.find("123405678") != std::string::npos)
	{
		cout << "Find Answer!" << endl;
		return 1;
	}
	Q.pop();

	tem=Move(s,'r');
	if(tem!="")
		Q.push(tem);
	tem = Move(s, 'l');
	if (tem != "")
		Q.push(tem);
	tem = Move(s, 'u');
	if (tem != "")
		Q.push(tem);
	tem = Move(s, 'd');
	if (tem != "")
		Q.push(tem);
	return 0;
	}

int main()
{
	string S;
	//S即为输入。
	S = "145068732";
	print(S);
	Q.push(S);

	while (!fun()); //如果使用递归，则需要足够大的堆栈保留空间，因此我采用了循环处理结构。
	S = Q.front();
	cout << "最少需要 " << S.size() - 9 << "次移动:" << endl;
	cout <<  S.substr(9,S.length()-9).c_str() << endl;
	getchar();
	return 0;
}

