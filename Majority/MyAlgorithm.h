#pragma once
#include<vector>
#include<fstream>
#include <ctime>

namespace MyAlgorithm
{
	double random(double start, double end)
	{
		return start + (end - start)*std::rand() / (RAND_MAX + 1.0);
	}

	template<class T> T String2T(std::string &str)
	{
		if (str == "NOT FOUND!")
			return INT_MIN;
		T ANS;
		std::stringstream stream;
		stream << str;
		stream >> ANS;
		return ANS;
	}

	template<class T> std::string T2String(T input)
	{
		std::stringstream stream;
		stream << input;
		return stream.str();
	}

	template<class T> std::string VecT2String(std::vector<T> input, std::string spliter = ",")
	{
		std::stringstream tem;
		for (auto i : input)
			tem << i << spliter;
		return tem.str();
	}


	template<class T> class Algorithm
	{
	public:
		int generate_cases(const char *filename="defult_cases.txt",const int cases_nums=100) const
		{
		//生成测试样例。
		// filename1: 样例写入文件名
		//int : 1 已经存在 不重新生成
		//	     0 成功生成并写入
		//		-1 未成功生成
			std::ifstream fin(filename);
			if (fin)
				return 1;
			std::ofstream outfile;
			outfile.open(filename, std::ios::out);
			std::vector<int> CASE;
			std::srand(unsigned(std::time(0)));
			for (int i = 0; i < cases_nums; i++)
			{
				CASE = GENERATE_TEST_CASE();
				for (auto j = CASE.begin(); j != CASE.end(); j++)
					outfile << *j << ',';
				outfile << std::endl;
			}
			outfile.close();
			return 0;
		}
		virtual std::string MAIN_ALGORITHM(std::vector<T>)=0 ;
		virtual std::vector<int> GENERATE_TEST_CASE()const = 0 ;
	};


}