#pragma once
#include<vector>
#include<algorithm>
#include<iostream>
namespace Astar
{
	template<typename T> class Configure;
	template<typename T> class Status
	{
	public:
		T t;
		double h, g,f;
		Status(T s){	t = s;	}
		void Update(Configure<T> C,Status<T> S)
		{
		h = C.Calculate_H(*this, S);
		g = C.Calculate_G(*this);
		f = h + g;
		C.OldUpdate(this->t);
		}
		bool operator==(Status<T> S2)
		{
			return t == S2.t;
		}
		bool operator==(T S2)
		{
			return t == S2;
		}
	};

	template<typename T>
	std::ostream & operator<<(std::ostream& out, const Status<T> &s)
	{
		out << s.t << std::endl<<"G:"<<s.g<<"  H:"<<s.h<<"  F"<<s.f<<std::endl;
		return out;
	}

	template<typename T>
	bool comp(Status<T> &i, Status<T> &j) { return (i.f<j.f);}

	template<typename T> class Configure
	{
	private:
		double(*H)(const T  &, const T   &);  //H估值函数，用来衡量当前节点到目标节点的距离
		double(*G)(const T &);  // G估值函数，衡量初始节点到当前节点的距离
		bool(*EQUAL)(const T &, const T &); //判断是否相等
		std::vector<T>(*EXPEND)(T);
		void(*OTHERS)(T &);
	public:
		Configure(double(*h)(const T  &, const T   &), double(*g)(const T &), bool(*equal)(const T &, const T &), std::vector<T>(*expend)(T),void(*other)(T&))
		{
			H = h; G = g; 
			EQUAL = equal; 
EXPEND = expend; OTHERS = other;
		}
		//double Calculate_H(const T * t1,const T * t2)
		//{return this->H(*t1, *t2);	}
		double Calculate_H(const Status<T> & S1, const Status<T> & S2)
		{
			return this->H(S1.t, S2.t);
		}
		double Calculate_G(const Status<T> & S) { return this->G(S.t); }
		bool IS_EAQUE(const Status<T> &S1, const Status<T> &S2)
		{
			return EQUAL(S1.t, S2.t);
		}
		std::vector<Status<T>> EXPEND_S(const Status<T> &S)
		{
			std::vector<Status<T>> output;
			auto tem = EXPEND(S.t);
			for (auto i : tem)
			{
				OTHERS(i);
				Status<T> j(i);
				output.push_back(j);
			}
			return output;
		}

		void OldUpdate(T &S)
		{
			OTHERS(S);
		}

		typename std::vector<Status<T>>::iterator Find(std::vector<Status<T>> & List, Status<T> S)
		{
			std::vector<Status<T>>::iterator p=List.end();
			for (auto p = List.begin(); p != List.end(); p++)
			{
				if (*p == S)
					return p;
			}
			return p;
		}

	};


	template<typename T> T AStar(const T & start, const T & target, Configure<T> C) 
	{
		std::vector<Status<T>> Open, Close;
		Status<T> START(start);
		Status<T> TARGET(target);
		START.Update(C, TARGET);
		Open.push_back(START);
		int step = 0;
		while (Open.size())
		{
//std::cout << " fun:" << step++ << "  Size of Open:" << Open.size() <<std::endl;
			Status<T> tem = *Open.begin();
//std::cout << tem;
			//if (C.IS_EAQUE(tem.t, target))
			if(tem.t==target)
				return tem.t;
			Close.push_back(tem);
			std::vector<Status<T>> nex = C.EXPEND_S(tem);
 			for (std::vector<Status<T>>::iterator it = nex.begin(); it != nex.end(); it++)
			{
				it->Update(C, TARGET);
				std::vector<Status<T>>::iterator index_Open = std::find(Open.begin(), Open.end(), *it);
					//C.Find(Open, *it);
				std::vector<Status<T>>::iterator index_Close = std::find(Close.begin(), Close.end(), *it);
					//C.Find(Close, *it);
				if (index_Open != Open.end() || index_Close != Close.end())
				{				
					if (index_Open != Open.end() && it->f < index_Open->f)//属于Open;
						index_Open->f = it->f;
				}
				else
					Open.push_back(*it);
			}
			nex.clear();
			Open.erase(Open.begin());
			std::sort(Open.begin(), Open.end(),comp<T>);
		}
		return start;//表示没找到结果
	}


	template<typename T> T AStar(const T & start, const T & target, Configure<T> C,int & Open_nums,int & Close_nums, int & extended_nums)
	{
		//Open_nums = 0; Close_nums = 0; extended_nums = 0;
		std::vector<Status<T>> Open, Close;
		Status<T> START(start);
		Status<T> TARGET(target);
		START.Update(C, TARGET);
		Open.push_back(START);
		int step = 0;
		while (Open.size())
		{
			//std::cout << " fun:" << step++ << "  Size of Open:" << Open.size() <<std::endl;
			Status<T> tem = *Open.begin();
			//std::cout << tem;
			//if (C.IS_EAQUE(tem.t, target))
			if (tem.t == target)
				return tem.t;
			Close.push_back(tem);
			extended_nums += 1;
			std::vector<Status<T>> nex = C.EXPEND_S(tem);
			for (std::vector<Status<T>>::iterator it = nex.begin(); it != nex.end(); it++)
			{
				it->Update(C, TARGET);
				std::vector<Status<T>>::iterator index_Open = std::find(Open.begin(), Open.end(), *it);
				//C.Find(Open, *it);
				std::vector<Status<T>>::iterator index_Close = std::find(Close.begin(), Close.end(), *it);
				//C.Find(Close, *it);
				if (index_Open != Open.end() || index_Close != Close.end())
				{
					if (index_Open != Open.end() && it->f < index_Open->f)//属于Open;
						index_Open->f = it->f;
				}
				else
					Open.push_back(*it);
			}
			nex.clear();
			Open.erase(Open.begin());
			std::sort(Open.begin(), Open.end(), comp<T>);
			Open_nums = Open.size();
			Close_nums = Close.size();
		}
		return start;//表示没找到结果
	}

};