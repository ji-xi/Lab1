#pragma once

#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <time.h>
#include <functional>
#include <vector>
#include <stdexcept>

//Функция нахождения максимального элемента
int get_max(std::vector<int> v)
{
	if (v.empty()) throw "Empty list";

	int max = v.front();
	for (int x : v)
	{
		if (x > max) max = x;
	}
	return max;
}

//Функция нахождения максимального элемента
int get_max(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	if (begin == end) throw "Empty list";

	int max = *begin;
	for (auto it = begin; it != end; it++)
	{
		if (*it > max) max = *it;
	}
	return max;
}

//Функтор для transform
class funct_transform
{
private:
	int max;
public:
	funct_transform(int _max) : max(_max) {
	}
	int operator ( ) (int el)
	{
		return (el - max);
	}
};

//Функтор для for_each
class funct_for_each
{
private:
	int max;
public:
	funct_for_each(int _max) : max(_max) {
	}
	void operator ( ) (int& el) const
	{
		el = el - max;
	}
};

//Заполнение файла рандомными числами в цикле
std::fstream random_file(std::string file_name, int N, int M)
{
	srand(time(NULL));
	std::fstream fout(file_name, std::ios::out);
	for (int i = 0; i < N; i++)
	{
		fout << rand() % (2 * M + 1) - M << "\n";
	}
	fout.close();
	return fout;
}

//Заполнение файла рандомными числами с использованием generate
std::fstream random_file_generate(std::string file_name, int N, int M)
{
	std::vector<int> v(N);
	std::fstream fout(file_name, std::ios::out);
	std::generate(v.begin(), v.end(), rand);
	for (int i = 0; i < N; i++)
	{
		fout << v[i] % (2 * M + 1) - M << "\n";
	}
	fout.close();
	return fout;
}

//Функция, получающая файл на вход, и возвращающую последовательный контейнер, заполненный числами из файла
std::vector<int> get_vector_from_file(std::string file_name)
{
	std::vector<int> v;
	int x;
	std::fstream fin(file_name, std::ios::in);
	if (fin.is_open())
	{
		while (fin >> x)
		{
			v.push_back(x);
		}
		fin.close();
	}
	else
		std::cout << "Файла не существует!" << std::endl;
	return v;
}

//Функция modify, выполняющую преобразование полученного контейнера. 
std::vector<int> modify(std::vector<int> v)
{
	try
	{
		int max = get_max(v);
		for (auto it = v.begin(); it != v.end(); it++)
		{
			*it = *it - max;
		}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}
	return v;
}

//Перегруженная функция modify(с поступающими итераторами)
void modify(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	try
	{
			int max = get_max(begin, end);
			for (auto it = begin; it != end; it++)
			{
				*it = *it - max;
			}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}
}

//Преобразование с помощью transform
std::vector<int> modify_transform(std::vector<int> v_in)
{
	try
	{
		funct_transform funct(get_max(v_in));
		std::vector<int> v_out;
		v_out.resize(v_in.size());

		std::transform(v_in.begin(), v_in.end(), v_out.begin(), funct);
		return v_out;
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
		return v_in;
	}
}

//Преобразование с помощью for_each
std::vector<int> modify_for_each(std::vector<int> v_in)
{
	try
	{
		funct_for_each funct(get_max(v_in));
		std::for_each(v_in.begin(), v_in.end(), funct);
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}
	return v_in;
}

//Сумма
int vector_sum(std::vector<int> v)
{
	int sum = 0;
	for (int x : v)
	{
		sum += x;
	}
	return sum;
}

//Среднее арифметическое
double vector_average(std::vector<int> v)
{
	return (double)vector_sum(v) / v.size();
}

//Вывод в файл
void vector_to_file(std::vector<int> v, std::string file_name = "")
{
	std::fstream fout(file_name, std::ios::out);
	if (fout.is_open())
	{
		for (int x : v)
		{
			fout << x << std::endl;;
		}
		fout.close();
	}
	else
	{
		std::cout << "Ошибка";
	}
}

//Вывод в консоль
void  vector_to_console(std::vector<int> v)
{
	if (!v.empty())
	{
		std::cout << "[";
		for (int x : v)
		{
			std::cout << x << ", ";
		}
		std::cout << "\b\b" << "]";
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Вектор пуст" << std::endl;
	}
}
