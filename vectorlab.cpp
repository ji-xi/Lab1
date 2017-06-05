// labvector.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "subfunk.h"

//  Харченко Евгения Анреевна 
//	3 - Вычесть из каждого числа максимальное из чисел.
//	а - вектор (std::vector)


void print_menu()
{
	std::cout << "________________________________________________________" << std::endl;
	std::cout << "Меню:" << std::endl;
	std::cout << " 1. Заполнить файл рандомными числами" << std::endl;
	std::cout << " 2. Заполнить файл рандомными числами с помощью generate" << std::endl;
	std::cout << " 3. Открыть контейнер" << std::endl;
	std::cout << " 4. Преобразование" << std::endl;
	std::cout << " 5. Преобразование(iterators)" << std::endl;
	std::cout << " 6. Преобразование(transform)" << std::endl;
	std::cout << " 7. Преобразование(foreach)" << std::endl;
	std::cout << " 8. Сумма" << std::endl;
	std::cout << " 9. Среднее арифметическое" << std::endl;
	std::cout << " 10. Сохранить в файл" << std::endl;
	std::cout << " 11. Вывести в консоль" << std::endl;
	std::cout << " 0. Выход" << std::endl;
	std::cout << "________________________________________________________" << std::endl;
	std::cout << "Ваша команда: ";
}

std::string input_file_name()
{
	std::string name;
	std::cout << "Введите имя файла(без расширения): " << std::endl;
	std::getline(std::cin, name);
	std::getline(std::cin, name);
	if (name == "") name = "testfile";
	return name + ".txt";
}

int main()
{
	std::vector<int> vect;
	std::string file_name;
	std::string str;
	int sub_index;
	int index;
	auto begin = vect.begin();
	auto end = vect.begin();

	setlocale(LC_ALL, "Russian");

	while (true)
	{
		print_menu();
		std::cin >> str;
		try
		{
			index = std::stoi(str);
			switch (index)
			{
			case 1: //Заполнить файл рандомными числами
				int N, M;
				file_name = input_file_name();
				std::cout << "Введите N: ";
				std::cin >> N;
				std::cout << "Введите M: ";
				std::cin >> M;
				if (M < 0) M = abs(M);
				random_file(file_name, N, M);
				break;

			case 2:	//Заполнить файл рандомными числами с помощью generate
				file_name = input_file_name();
				std::cout << "Введите N: ";
				std::cin >> N;
				std::cout << "Введите M: ";
				std::cin >> M;
				if (M < 0) M = abs(M);
				random_file_generate(file_name, N, M);
				break;

			case 3: //Открыть контейнер
				file_name = input_file_name();
				vect = get_vector_from_file(file_name);
				vector_to_console(vect);
				break;

			case 4: //Преобразование
				if (!vect.empty())
				{
					vector_to_console(vect);
					vect = modify(vect);
					vector_to_console(vect);
				}
				else
				{
					std::cout << "Вектор пуст" << std::endl;
				}
				break;

			case 5: //Преобразование(iterators)
				int a, b;
				a = b = sub_index = 0;
				if (!vect.empty())
				{
					vector_to_console(vect);
					while ((sub_index < 1) || (sub_index > 3))
					{
						std::cout << "-------------------------------------" << std::endl;
						std::cout << " 1. Преобразовать весь вектор" << std::endl;
						std::cout << " 2. Преобразовать на интервале [a, b)" << std::endl;
						std::cout << " 0. Отмена" << std::endl;
						std::cout << "-------------------------------------" << std::endl;
						std::cin >> sub_index;
					}
					switch (sub_index)
					{
					case 1:
						modify(vect.begin(), vect.end());
						vector_to_console(vect);
						break;

					case 2:
						std::cout << "a: ";
						std::cin >> a;
						std::cout << "b: ";
						std::cin >> b;
						if ((a >= b || a<1 || b<1 || a > (vect.size()+1) || b > (vect.size()+1)))
							std::cout << "Не верный диапазон" << std::endl;
						else
						{
							begin = vect.begin();
							end = vect.begin();
							std::advance(begin, a - 1);
							std::advance(end, b - 1);

							modify(begin, end);
							vector_to_console(vect);
						}
						break;

					case 0:
						break;

					default:
						std::cout << "Не верная команда" << std::endl;
						break;
					}
				}
				else
				{
					std::cout << "Список пуст" << std::endl;
				}
				break;

			case 6: //Преобразование(transform)
				if (!vect.empty())
				{
					vector_to_console(vect);
					vect = modify_transform(vect);
					vector_to_console(vect);
				}
				else
				{
					std::cout << "Вектор пуст" << std::endl;
				}
				break;

			case 7: //Преобразование(foreach)
				if (!vect.empty())
				{
					vector_to_console(vect);
					vect = modify_for_each(vect);
					vector_to_console(vect);
				}
				else
				{
					std::cout << "Список пуст" << std::endl;
				}
				break;

			case 8: //Сумма
				vector_to_console(vect);
				std::cout << "Сумма = " << vector_sum(vect) << std::endl;
				break;

			case 9: //Среднее арифметическое
				if (!vect.empty())
				{
					vector_to_console(vect);
					std::cout << "Среднее арифметическое = " << vector_average(vect) << std::endl;
				}
				else
				{
					std::cout << "Список пуст" << std::endl;
				}
				break;

			case 10: //Сохранить в файл
				if (!vect.empty())
				{
					file_name = input_file_name();
					vector_to_file(vect, file_name);
					vector_to_console(vect);
				}
				else
				{
					std::cout << "Вектор пуст" << std::endl;
				}
				break;

			case 11: //Вывести в консоль
				vector_to_console(vect);
				break;

			case 0: //Выход
				return 0;
				break;

			default:
				std::cout << "Не верная команда" << std::endl;
				break;
			}
		}
		catch (std::exception& e)
		{
			std::cout << "Не верная команда" << std::endl;
		}
	}
}

