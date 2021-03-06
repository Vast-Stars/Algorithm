#include<iostream>
#include<vector>
#include <sstream>
#include <climits> 
#include"MyAlgorithm.h"

template<class T> class Majority :public MyAlgorithm::Algorithm<T>
{
public:
	std::vector<int> GENERATE_TEST_CASE()const override
	{
		std::vector<int> Case;
		int target = std::rand();
		int i = MyAlgorithm::random(1, 1000); //
		int tem;
		for (int j = 0; j < i; j++)
		{
			tem = rand();
			if (tem % 2)
				Case.push_back(tem);
			else
				Case.push_back(target);
		}
		return Case;
	}

	std::vector<std::vector<int>> GENERATE_CASES(const int cases_nums = 100) const
	{
		//生成测试样例。
		std::vector<std::vector<int>> CASES;
		std::srand(unsigned(std::time(0)));
		for (int i = 0; i < cases_nums; i++)
			CASES.push_back(GENERATE_TEST_CASE());
		return CASES;
	}

	int RUN_TEST(std::vector<std::vector<int>> cases, const char *filename = "test_result.txt")
	{
		std::ofstream outfile;
		outfile.open(filename, std::ios::out);
		//std::vector<std::string> TEST_Ans; //Algorithm Result； 
		std::vector<clock_t> TEST_Time; // Running time；
		std::clock_t start = std::clock();
		for (auto example : cases)
		{
			outfile << MAIN_ALGORITHM(example) << ",";
			TEST_Time.push_back(std::clock() - start);
		}
		outfile << std::endl;
		for (auto i : TEST_Time)
			outfile << i << ";";
		outfile << std::endl;
		outfile.close();
		return 0;
	}
};

template<class T=int> class Majority_Origin :public Majority<T>
{
public:
	std::string MAIN_ALGORITHM(std::vector<T> INPUT) override
	{
		int count = 1;
		T target = INPUT[0];
		int size = INPUT.size();
		for (int i=1; i<size && count <= size/ 2; i++)
		{
			if (INPUT[i] == target)
				count++;
			else
			{
				count--;
				if (count == 0)
					if (i + 1 == size)
						return std::string("NOT FOUND!");
					else
						target = INPUT[i + 1];
			}
		}
		return MyAlgorithm::T2String(target);
	}

};

template<class T=int> class Majority_Advanced :public Majority<T>
{
public:
	std::string MAIN_ALGORITHM(std::vector<T> INPUT) override
	{
		int count = 1;
		T target = INPUT[0];
		int size = INPUT.size();
		int total_size = size;
		for (int i = 1; i<total_size && count <= size / 2; i++)
		{
			if (INPUT[i] == target)
				count++;
			else
			{
				count--;
				if (count == 0)
					if (i + 1 ==total_size)
						return std::string("NOT FOUND!");
					else
					{
						target = INPUT[i + 1];
						size = total_size- i - 1;
					}
			}
		}
		return MyAlgorithm::T2String(target);
	}
};

int main()
{
	Majority_Origin<int> algorithm;
	Majority_Advanced<int> algorithm_Advanced;

	//std::vector<int> input{1,1,2,3};
	//std::cout << A.MAIN_ALGORITHM(input) << std::endl;
	std::cout << MyAlgorithm::VecT2String<int>(std::vector<int>{1, 2, 3}) << std::endl;
	std::vector<std::vector<int>> CASES = algorithm.GENERATE_CASES(15000);
	algorithm.RUN_TEST(CASES, "Origin_Version_15000.txt");
	algorithm_Advanced.RUN_TEST(CASES, "Advanced_Version_15000.txt");
	std::cout << "OK" << std::endl;
    return 0;
}

