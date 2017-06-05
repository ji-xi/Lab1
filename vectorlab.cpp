// labvector.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "subfunk.h"

//  �������� ������� �������� 
//	3 - ������� �� ������� ����� ������������ �� �����.
//	� - ������ (std::vector)


void print_menu()
{
	std::cout << "________________________________________________________" << std::endl;
	std::cout << "����:" << std::endl;
	std::cout << " 1. ��������� ���� ���������� �������" << std::endl;
	std::cout << " 2. ��������� ���� ���������� ������� � ������� generate" << std::endl;
	std::cout << " 3. ������� ���������" << std::endl;
	std::cout << " 4. ��������������" << std::endl;
	std::cout << " 5. ��������������(iterators)" << std::endl;
	std::cout << " 6. ��������������(transform)" << std::endl;
	std::cout << " 7. ��������������(foreach)" << std::endl;
	std::cout << " 8. �����" << std::endl;
	std::cout << " 9. ������� ��������������" << std::endl;
	std::cout << " 10. ��������� � ����" << std::endl;
	std::cout << " 11. ������� � �������" << std::endl;
	std::cout << " 0. �����" << std::endl;
	std::cout << "________________________________________________________" << std::endl;
	std::cout << "���� �������: ";
}

std::string input_file_name()
{
	std::string name;
	std::cout << "������� ��� �����(��� ����������): " << std::endl;
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
			case 1: //��������� ���� ���������� �������
				int N, M;
				file_name = input_file_name();
				std::cout << "������� N: ";
				std::cin >> N;
				std::cout << "������� M: ";
				std::cin >> M;
				if (M < 0) M = abs(M);
				random_file(file_name, N, M);
				break;

			case 2:	//��������� ���� ���������� ������� � ������� generate
				file_name = input_file_name();
				std::cout << "������� N: ";
				std::cin >> N;
				std::cout << "������� M: ";
				std::cin >> M;
				if (M < 0) M = abs(M);
				random_file_generate(file_name, N, M);
				break;

			case 3: //������� ���������
				file_name = input_file_name();
				vect = get_vector_from_file(file_name);
				vector_to_console(vect);
				break;

			case 4: //��������������
				if (!vect.empty())
				{
					vector_to_console(vect);
					vect = modify(vect);
					vector_to_console(vect);
				}
				else
				{
					std::cout << "������ ����" << std::endl;
				}
				break;

			case 5: //��������������(iterators)
				int a, b;
				a = b = sub_index = 0;
				if (!vect.empty())
				{
					vector_to_console(vect);
					while ((sub_index < 1) || (sub_index > 3))
					{
						std::cout << "-------------------------------------" << std::endl;
						std::cout << " 1. ������������� ���� ������" << std::endl;
						std::cout << " 2. ������������� �� ��������� [a, b)" << std::endl;
						std::cout << " 0. ������" << std::endl;
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
							std::cout << "�� ������ ��������" << std::endl;
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
						std::cout << "�� ������ �������" << std::endl;
						break;
					}
				}
				else
				{
					std::cout << "������ ����" << std::endl;
				}
				break;

			case 6: //��������������(transform)
				if (!vect.empty())
				{
					vector_to_console(vect);
					vect = modify_transform(vect);
					vector_to_console(vect);
				}
				else
				{
					std::cout << "������ ����" << std::endl;
				}
				break;

			case 7: //��������������(foreach)
				if (!vect.empty())
				{
					vector_to_console(vect);
					vect = modify_for_each(vect);
					vector_to_console(vect);
				}
				else
				{
					std::cout << "������ ����" << std::endl;
				}
				break;

			case 8: //�����
				vector_to_console(vect);
				std::cout << "����� = " << vector_sum(vect) << std::endl;
				break;

			case 9: //������� ��������������
				if (!vect.empty())
				{
					vector_to_console(vect);
					std::cout << "������� �������������� = " << vector_average(vect) << std::endl;
				}
				else
				{
					std::cout << "������ ����" << std::endl;
				}
				break;

			case 10: //��������� � ����
				if (!vect.empty())
				{
					file_name = input_file_name();
					vector_to_file(vect, file_name);
					vector_to_console(vect);
				}
				else
				{
					std::cout << "������ ����" << std::endl;
				}
				break;

			case 11: //������� � �������
				vector_to_console(vect);
				break;

			case 0: //�����
				return 0;
				break;

			default:
				std::cout << "�� ������ �������" << std::endl;
				break;
			}
		}
		catch (std::exception& e)
		{
			std::cout << "�� ������ �������" << std::endl;
		}
	}
}

