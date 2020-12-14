#include <iostream>
#include <random>
#include <fstream>

using namespace std;

extern "C"
{
	void mod1(int* array_mod1, int* NumArray, int NumRanDat, int Xmin);
	void mod2(int* array_mod1, int NumRanDat, int* LGrInt, int NInt, int Xmin, int Xmax, int* array_mod2);
}

int main()
{
	setlocale(0, "");
	int NumRanDat;
	int Xmin, Xmax;
	int	NInt;
	ofstream open_file;
	open_file.open("opened_file.txt");
	cout << "Введите длину массива псевдослучайных целых чисел\n";
	cout << "(Длина массива не может быть больше 16*1024 и меньше 0)\n";
	cin >> NumRanDat;
	if (NumRanDat > 16 * 1024 || NumRanDat < 0)
	{
		while (NumRanDat > 16 * 1024 || NumRanDat < 0)
		{
			cout << "Вы ввели неправильную длину массива, попробуйте еще раз\n";
			cin >> NumRanDat;
		}
	}
	cout << "\nВведите диапазон изменения массива (минимальное и максимальное значения\n";
	cout << "(если максимальное значение будет меньше минимального, то значения поменяются местами)\n";
	cin >> Xmin;
	cin >> Xmax;
	if (Xmax < Xmin)
	{
		swap(Xmax, Xmin);
	}
	cout << "\nВведите количество интервалов, на которые разбивается диапозон изменения массива\n";
	cout << "Количество интервалов должно быть больше 0, но меньше 24\n";
	cin >> NInt;
	if (NInt < 0 || NInt > 24)
	{
		while (NInt > 24 || NInt < 0)
		{
			cout << "Вы ввели неправильное количество интервалов, попробуйте еще раз\n";
			cin >> NInt;
		}
	}
	int* NumArray = new int[NumRanDat];
	int* LGrInt = new int[NInt];
	int* array_mod1 = new int[abs(Xmax - Xmin) + 1];
	int* array_mod2 = new int[NInt + 1];
	cout << "\nВведите левые границы:\n";
	for (int i = 0; i < NInt; i++)
	{
		cin >> LGrInt[i];
		if (LGrInt[i] < Xmin || LGrInt[i] > Xmax)
		{
			while (LGrInt[i] < Xmin || LGrInt[i] > Xmax)
			{
				cout << "Вы ввели неправильную левую границу, попробуйте еще раз\n";
				cin >> LGrInt[i];
			}
		}
	}

	for (int i = 0; i < NumRanDat; i++)
	{
		NumArray[i] = rand() % (Xmax - Xmin + 1) + Xmin;
	}
	for (int i = 0; i < abs(Xmax - Xmin) + 1; i++)
	{
		array_mod1[i] = 0;
	}
	mod1(array_mod1, NumArray, NumRanDat, Xmin);
	cout << "\n";
	for (int i = 0; i < NInt + 1; i++) 
	{
		array_mod2[i] = 0;
	}
	mod2(array_mod1, NumRanDat, LGrInt, NInt, Xmin, Xmax, array_mod2);
	cout << "\nПсевдослучайные целые числа: ";
	open_file << "\nПсевдослучайные целые числа: ";
	for (int i = 0; i < NumRanDat; i++)
	{
		cout << NumArray[i] << " ";
		open_file << NumArray[i] << " ";
	}
	cout << "\n";
	open_file << "\n";
	cout << "\nРаспределение по единичным интервалам: ";
	open_file << "\nРаспределение по единичным интервалам: ";
	cout << "\n";
	open_file << "\n";
	for (int i = 0; i < abs(Xmax - Xmin) + 1; i++)
	{
		cout << Xmin + i << " ";
		open_file << Xmin + i << " ";
	}
	cout << "\n";
	open_file << "\n";
	for (int i = 0; i < abs(Xmax - Xmin) + 1; i++)
	{
		cout << array_mod1[i] << " ";
		open_file << array_mod1[i] << " ";
	}
	cout << "\n";
	open_file << "\n";
	cout <<" Номер интервала \t  Левая граница интервала \t Колисество чисел в интервале\n";
	open_file << "Номер интервала \t Левая граница интервала \t Количество чисел в интервале\n";
	cout << " " << 0 << " \t\t\t\t " << Xmin << " \t\t\t\t " << array_mod2[0] << "\n";
	open_file << " " << 0 << " \t\t\t\t " << Xmin << " \t\t\t\t " << array_mod2[0] << "\n";
	for (int i = 1; i < NInt+1; i++)
	{
		cout << " " << i << " \t\t\t\t " << LGrInt[i - 1] + Xmin << " \t\t\t\t " << array_mod2[i] << "\n";
		open_file << " " << i << " \t\t\t\t " << LGrInt[i - 1] + Xmin << " \t\t\t\t " << array_mod2[i] << "\n";
	}

	delete[] array_mod1;
	delete[] array_mod2;
	delete[] LGrInt;
	delete[] NumArray;

	return 0;
}