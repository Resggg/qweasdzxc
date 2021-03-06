// dz.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::vector<int>> Implmult(std::vector<std::vector<int>> a, std::vector<std::vector <int>> b)
{
	std::vector<std::vector<int>> result;
	for (auto & x : a)
		for (auto &y : b)
		{
			std::vector<int> buff;
			for (auto &xi : x)
				buff.push_back(xi);
			for (auto &yi : y)
			{
				if (std::find(buff.begin(), buff.end(), yi) == buff.end())
					buff.push_back(yi);
			}
			result.push_back(buff);
		}
	return result;
}


std::vector<int> Cover(bool  **mat, const std::vector<int> & nepokr, const std::vector<int> & ignor, std::vector<std::vector<int>> &met, std::vector<int> &ves)
{
	std::vector<int> a;
	std::vector<std::vector<std::vector<int>>> patrik;
	patrik.resize(nepokr.size());
	int i = 0;
	for (auto & x : nepokr)
	{
		int j = 0;
		for (auto & y : ignor)
		{
			std::vector <int> K;
			if (mat[y][x] == true)
			{
				K.push_back(y);
				patrik[i].push_back(K);
			}
			j++;
		}
		i++;
	}

	while (patrik.size() > 1)
	{
		std::vector <std::vector<int>> sets;
		sets = Implmult(patrik[0], patrik[1]);
		patrik.erase(patrik.begin(), patrik.begin() + 2);
		if (sets.size())
			patrik.push_back(sets);
	}
	int wei = INT_MAX;
	int l = -1;
	int p = -1;
	for (int i = 0; i < patrik.size(); i++)
	{
		for (int j = 0; j < patrik[i].size(); j++)
		{
			int cur_w = 0;
			for (auto &x : patrik[i][j])
			{
				cur_w += ves[x];
			}
			if (cur_w < wei)
			{
				wei = cur_w;
				l = i;
				p = j;
			}
		}
	}
	for (auto &x : patrik[l][p])
	{
		a.push_back(x);
	}
	return  a;
}




class Metod
{
public:
	Metod(std::vector<std::vector<int>> met, std::vector<int> ves, std::vector<int> tasks);
	std::vector<int> solList();
	void feel();

	~Metod();

private:
	bool **matr;
	std::vector<int> _tasks;
	std::vector<std::vector<int>> _met;
	std::vector<int> _ves;

};

Metod::Metod(std::vector<std::vector<int>> met, std::vector<int> ves, std::vector<int> tasks) : _met(met), _ves(ves), _tasks(tasks)
{

}

std::vector<int> Metod::solList()
{
	std::vector<int> sl;
	std::vector<int> pokr;
	std::vector <int> consider;
	for (int i = 0; i < _tasks.size(); i++)
	{
		int kol = 0;
		int cec;
		for (int j = 0; j < _met.size(); j++)
		{
			if (matr[j][i] == true)
			{
				kol++;
				cec = j;
			}
		}
		if (kol == 1)
		{
			//int object =cec;
			bool X3 = false;
			for (auto & x : sl)
			{
				if (x == cec)
				{
					X3 = true;
				}
			}
			if (!X3)
			{
				for (int k = 0; k < _tasks.size(); k++)
				{
					if (matr[cec][k] == true && std::find(pokr.begin(), pokr.end(), k) == pokr.end())
					{
						pokr.push_back(k);
					}
				}
				consider.push_back(cec);
				sl.push_back(cec);
			}
		}
	}
	if (pokr.size() == _tasks.size())
		return sl;
	std::vector<int> nepokr;
	for (int i = 0; i < _tasks.size(); i++)
	{
		if (std::find(pokr.begin(), pokr.end(), i) == pokr.end())
			nepokr.push_back(i);
	}
	std::vector<int> ignor;
	for (int i = 0; i < _met.size(); i++)
	{
		if (std::find(consider.begin(), consider.end(), i) == consider.end())
			ignor.push_back(i);
	}
	std::vector <int> b = Cover(matr, nepokr, ignor, _met, _ves);
	for (auto &x : b)
	{
		sl.push_back(x);
	}
	return sl;
}
void Metod::feel()
{
	matr = new bool*[_met.size()];
	for (int i = 0; i < _met.size(); i++)
	{
		matr[i] = new bool[_tasks.size()];
	}

	for (int i = 0; i < _met.size(); i++)
		for (int j = 0; j < _tasks.size(); j++)
			matr[i][j] = false;

	for (int i = 0; i < _met.size(); i++)
	{
		for (auto &j : _met[i])
		{
			matr[i][j] = true;
		}
	}
}
Metod::~Metod()
{
	for (int i = 0; i < _met.size(); i++)
	{
		delete[] matr[i];
	}
	delete[] matr;
}

int main(int argc, char *argv[])
{
	ifstream F1(argv[1]);
    ifstream F2(argv[2]);
    ifstream F3(argv[3]);
	std::vector<int> tasks_;
	std::vector<std::vector<int>> met_;
	std::vector<int> ves_;
	std::vector<int> met1;
	int a;
	int b;
	int c;
	F1 >> a;
	for (int i=0; i<a; i++)
	{
		f1 >> b;
		tasks_.pushback(b);
	}
	F1 >> a;
	for (int i=0; i<a; i++)
	{
		f1 >> b;
		ves_.pushback(b);
	}
	for (int i=0; i<a; i++)
	{
		F1 >> c;
		for (int i=0; i<c; i++)
		{
			f1 >> b;
			met1.pushback(b);
		}
		met_.pushback(met1);
		met1.clear();
	}

	
	Metod metod(met_, ves_, tasks_);
	metod.feel();
	for (auto &x : metod.solList())
	{
		F2<< x << " ";
	}
	//std::cout << std::endl;
	//system("pause");

    return 0;
}

