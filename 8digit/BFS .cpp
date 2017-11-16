
#include "stdafx.h"
#include <iostream>
#include <vector>
#include<queue>
#define  SIZE 3
using namespace std;


queue<string> Q;//���ڴ���������ַ����Ķ���

void print(const string s)
//���ַ�����������ʽ���
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
//����λ��ָ�������ƶ��õ��µ�״̬��
//ע��1������Խ��  2����ֹ����Ƕ�ף�����������һ������֮�������ơ�
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
	//S��Ϊ���롣
	S = "145068732";
	print(S);
	Q.push(S);

	while (!fun()); //���ʹ�õݹ飬����Ҫ�㹻��Ķ�ջ�����ռ䣬����Ҳ�����ѭ������ṹ��
	S = Q.front();
	cout << "������Ҫ " << S.size() - 9 << "���ƶ�:" << endl;
	cout <<  S.substr(9,S.length()-9).c_str() << endl;
	getchar();
	return 0;
}

