#include <iostream>
#include <iomanip>
#include<vector>
#include "AStar.h"
#include<fstream>
#include <string>
// The Side length of Matrix;  SIZE=n means (n*n-1)digit problem.
#define SIZE 3
using namespace std;

struct status
{
	int m[SIZE*SIZE];
	int x, y;
	string path = " ";
	status()
	{
		memset(m, 0, sizeof(int) * SIZE*SIZE);
	}
	status(int *p)
	{
		memcpy(m, p, sizeof(int) * SIZE*SIZE);
	}
	void operator= (initializer_list<int> p)
	{
		copy(p.begin(), p.end(), m);
	}
	bool operator==(const status &b)
	{
		for (int i = 0; i < SIZE*SIZE; i++)
			if (*(this->m + i) != *(b.m + i))
				return false;
		return true;
	}


};

std::ostream & operator<<(std::ostream& out,const status &s)
{
	int i = 0;
	out << "Matrix:" << std::endl;
	while (i < SIZE*SIZE)
	{
		out << setw(4) << *(s.m + i);
		if (++i % SIZE == 0)
			out << std::endl;

	}
	return out;
}

status generate_Target()
{
	int  Target[SIZE*SIZE] = { 0 };
	int count, i, j, k, kend, lend;
	kend = SIZE / 2;
	lend = SIZE;
	count = 1;
	for (i = 0, j = 0, k = 0; k<kend; k++)
	{
		Target[SIZE*i + j] = count++;
		for (j++; j<lend; j++)
			Target[SIZE*i + j] = count++;

		for (i++, j--; i<lend; i++)
			Target[SIZE*i + j] = count++;

		for (i--, j--; j >= k; j--)
			Target[SIZE*i + j] = count++;

		for (i--, j++; i>k; i--)
			Target[SIZE*i + j] = count++;

		i++; j++; lend--;
	}
	if (SIZE % 2 != 0) Target[i*SIZE + j] = 0;
	return status(Target);
}

int reverse_nums(int a[SIZE*SIZE])
{
	int counter = 0;
	for (int i = 0; i < SIZE*SIZE; i++)
	{
		if (*(a + i) == 0)
			continue;
		for (int j = SIZE*SIZE - 1; j >i; j--)
		{
			if (*(a + i) < *(a + j))
				counter++;
		}
	}
	return counter;
}

bool valid_case(int a[SIZE*SIZE], int b[SIZE*SIZE])
{
	return reverse_nums(a) % 2 == reverse_nums(b) % 2 ? true : false;
}

double h(const status & s, const status  & TARGET)
{
	int h = 0, i = 0;
	for (i = 0; i < SIZE*SIZE; i++)
		if (*(s.m + i) != *(TARGET.m + i))
			h++;
	return h;
}

int find_num(int target,const int * array)
{
	for (int i = 0; i < SIZE*SIZE; i++)
		if (*(array + i) == target)
			return i;
}

double h1(const status & s, const status  & TARGET)
{
	int h = 0, i = 0;
	for (i = 0; i < SIZE*SIZE; i++)
		h += abs(i - find_num(*(s.m+i),TARGET.m));
	return h;
}

std::vector<int> find_xy(int target, const int * array)
{
	for (int i = 0; i < SIZE*SIZE; i++)
		if (*(array + i) == target)
			return vector<int>{i / SIZE, i%SIZE};
}

double h2(const status & s, const status  & TARGET)
{
	int h = 0, i = 0;
	int x,y;
	for (i = 0; i < SIZE*SIZE; i++)
	{
		x = i / SIZE; y = i%SIZE;
		std::vector<int> tem = find_xy(*(s.m + i), TARGET.m);
		h += (abs(tem[0] - x) + abs(tem[1] - y));
	}
	return h;
}

double h_bfs(const status & s, const status  & TARGET) { return 0; }
double g(const status  & s)
{
	return s.path.size()-1;
}

bool ifsame(const status  & s, const status  & TARGET)
{
	for (int i = 0; i < SIZE*SIZE; i++)
		if (*(s.m + i) != *(TARGET.m + i))
			return false;
	return true;
}

void update(status & s)
{
	for (int i = 0; i < SIZE*SIZE; i++)
	{
		if (s.m[i] == 0)
		{
			s.x = i / SIZE;
			s.y = i%SIZE;
		}
	}
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
		if (s.y == SIZE - 1 || s.path.back() == 'l')
			return zero;
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
			s.m[z_location] = s.m[z_location - 1];
			s.m[z_location - 1] = 0;
			s.path += 'l';
		}
		break;
	}
	case 'u':
	{
		if (s.x == 0 || s.path.back() == 'd')
			return zero;
		else
		{
			s.m[z_location] = s.m[z_location - SIZE];
			s.m[z_location - SIZE] = 0;
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
			s.m[z_location] = s.m[z_location + SIZE];
			s.m[z_location + SIZE] = 0;
			s.path += 'd';
		}
		break;
	}
	}
	return s;
}

std::vector<status>::const_iterator Find(vector<status>& ss, const status& a)
{
	vector<status>::const_iterator p = ss.end();

	for (p = ss.begin(); p != ss.end(); p++)
	{
		if (memcmp(p->m, a.m, sizeof(a.m)) == 0)
			return p;
	}
	return p;
}

vector<status> Generate_Next(const status a)
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

double random(double start, double end)
{
	return start + (end - start)*std::rand() / (RAND_MAX + 1.0);
}

status Generate_Case(status start, int depth)
{
	int tem;
	status t;
	while (depth)
	{
		 tem = random(1, 1000);

		switch (tem % 4)
		{
		case 0: t = Move(start, 'l'); break;
		case 1: t = Move(start, 'r'); break;
		case 2: t = Move(start, 'u'); break;
		case 3: t = Move(start, 'd'); break;
		}
		if (t.x!=-1)
		{
			start = t;
			update(start);
			depth--;
		}
	}
	return start;
}

std::vector<status> Generate_Cases(const status target, int depth,int MIN_DEPTH=0)
{
	std::vector<status> output;
	std::srand(unsigned(std::time(0)));
	while (depth-- > MIN_DEPTH)
		output.push_back(Generate_Case(target, depth));
	return output;
}

void Test(const status & target)
{
#define DEPTH 16
	Astar::Configure<status> C(h, g, ifsame, Generate_Next, update);
	Astar::Configure<status> C1(h1, g, ifsame, Generate_Next, update);
	Astar::Configure<status> C2(h2, g, ifsame, Generate_Next, update);
	Astar::Configure<status> C_BFS(h_bfs, g, ifsame, Generate_Next, update);
	std::vector<status> cases = Generate_Cases(target, DEPTH+5,5);

	std::ofstream outfile;
	outfile.open("test.txt", std::ios::out);
	outfile << "TEST CASES:" << endl;
	for (auto i : cases)
		outfile << i << " " << i.path << endl;

	double Time[4][DEPTH] = { 0 };
	int Open[4][DEPTH] = { 0 };
	int Close[4][DEPTH] = { 0 };
	int Extended[4][DEPTH] = { 0 };
	string path[4][DEPTH];

	std::clock_t  st;
	for (int i=0;i<DEPTH;i++)
	{
		//cout << cases[i];
		cases[i].path = " ";
		 st = std::clock();
		auto tem=Astar::AStar<status>(cases[i], target, C,Open[0][i],Close[0][i],Extended[0][i]);
		path[0][i] = tem.path;
		Time[0][i] = std::clock() - st;

		st = std::clock();;
		tem = Astar::AStar<status>(cases[i], target, C1, Open[1][i], Close[1][i], Extended[1][i]);
		path[1][i] = tem.path;
		Time[1][i] = std::clock() - st;

		 st = std::clock();
		 tem = Astar::AStar<status>(cases[i], target, C2, Open[2][i], Close[2][i], Extended[2][i]);
		path[2][i] = tem.path;
		Time[2][i] = std::clock() - st;

		  st = std::clock();
		  tem = Astar::AStar<status>(cases[i], target, C_BFS, Open[3][i], Close[3][i], Extended[3][i]);
		path[3][i] = tem.path;
		Time[3][i] = std::clock() - st;
	}


	outfile << "Open:[";
	for (int i = 0; i < 4; i++)
	{
		outfile << 'H' << i << ':' << endl<<'[';
		for (int j = 0; j < DEPTH; j++)
			outfile << Open[i][j]<<' ';
		outfile << ']' << endl;
	}

	outfile << "Close:[";
	for (int i = 0; i < 4; i++)
	{
		outfile << 'H' << i << ':' << endl<<'[';
		for (int j = 0; j < DEPTH; j++)
			outfile << Close[i][j]<<' ';
		outfile << ']' << endl;
	}

	outfile << "Extended:[";
	for (int i = 0; i < 4; i++)
	{
		outfile << 'H' << i << ':' << endl << '[';
		for (int j = 0; j < DEPTH; j++)
			outfile << Extended[i][j] << ' ';
		outfile << ']' << endl;
	}

	outfile << "Time:[";
	for (int i = 0; i < 4; i++)
	{
		outfile << 'H' << i << ':' << endl << '[';
		for (int j = 0; j < DEPTH; j++)
			outfile << Time[i][j] << ' ';
		outfile << ']' << endl;
	}
	outfile << "Path:[";
	for (int i = 0; i < 4; i++)
	{
		outfile << 'H' << i << ':' << endl << '[';
		for (int j = 0; j < DEPTH; j++)
			outfile << path[i][j] << ' ';
		outfile << ']' << endl;
	}

	outfile << "Length:[";
	for (int i = 0; i < 4; i++)
	{
		outfile << 'H' << i << ':' << endl << '[';
		for (int j = 0; j < DEPTH; j++)
			outfile << path[i][j].length()-1 << ' ';
		outfile << ']' << endl;
	}


	outfile.close();
}

int main()
{
	status TARGET = generate_Target();
	update(TARGET);
	status S;
	//S = { 1 ,2,3,8,4,0,7,6,5 };
	S = { 1,2,3,8,4,5,0,7,6 };
	//S = { 7,5,3,1,6,4,2,8,0 };
	//update(S);

	Test(TARGET);


//	cout<<h(S, TARGET);
	//if (!valid_case(S.m, TARGET.m))
	//{
	//	cout << "Invalid input!" << endl;	return -1;
	//}

	//Astar::Configure<status> C(h, g, ifsame, Generate_Next, update);
	//Astar::Configure<status> C1(h1, g, ifsame, Generate_Next, update);
	//Astar::Configure<status> C2(h2, g, ifsame, Generate_Next, update);
	//Astar::Configure<status> C_BFS(h_bfs, g, ifsame, Generate_Next, update);
	//status answer;
	//for(int i=1;i>0;i--)
	//	 answer = Astar::AStar<status>(S, TARGET,C2);
	//std::string path = answer.path;

	//for (size_t i = 1; i<path.size(); i++)
	//{
	//	update(S);
	//	S = Move(S, path[i]);
	//	//cout << S;
	//}
	//cout << "Length:" << path.size() - 1;
	//getchar();


	return 0;
}