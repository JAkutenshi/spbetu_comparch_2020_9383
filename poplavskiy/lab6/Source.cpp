#include <iostream>
#include <fstream>
#include <windows.h>
#include <random>
#include <clocale>

using namespace std;

extern "C" { //подключаем модуль на языке ассемблера 
	void MYASM(short int* arr, short int* LGrInt, unsigned short* res, unsigned short NInt, unsigned short NumRanDat);
}

int main() {
	unsigned short int NumRanDat = 0; //длина массива псевдослучайных целых чисел
	short int xmin = 0, xmax = 0; //границы диапазона псевдослучайных чисел
	short int* arr; //массив псевдослучайных чисел
	unsigned short int NInt; //количество интервалов
	short int* LGrInt; //массив левых границ интервалов
	unsigned short int* res;//массив с количеством чисел в каждом интервале

	ofstream result("result.txt");

	setlocale(LC_CTYPE, "rus");

	do {
		cin.clear();
		cin.sync();
		cout << "Введите длину массива псевдослучайных чисел (<=16000): ";
		cin >> NumRanDat;
		cout << endl;
	} while (NumRanDat > 16000 || NumRanDat < 0);

	do {
		cin.clear();
		cin.sync();
		cout << "Введите xmin и xmax: ";
		cin >> xmin >> xmax;
		cout << endl;
	} while (xmax <= xmin);

	do {
		cin.clear();
		cin.sync();
		cout << "Введите количество интервалов (<=24): ";
		cin >> NInt;
	} while (NInt > 24 || NInt < 1);

	arr = new short int[NumRanDat];
	LGrInt = new short int[NInt];



	cout << "\nВведите левые границы интервалов:\n";
	cout << "1: " << xmin << endl << endl; //первая левая граница - начало диапазона, т.е. xmin
	LGrInt[0] = xmin;

	//ввод остальных границ
	for (int i = 1; i < NInt; i++) {
		do {
			cin.clear();
			cin.sync();
			cout << i + 1 << ": ";
			cin >> LGrInt[i];
			cout << endl;
		} while (LGrInt[i]<xmin || LGrInt[i]>xmax);
	}

	//сортировка массива границ (по убыванию, т.к в asm модуль передаем инвертированный массив)
	for (int j = 0; j < NInt - 1; j++) {
		for (int i = 0; i < NInt - j - 1; i++) {
			if (LGrInt[i] < LGrInt[i + 1]) {
				int b = LGrInt[i];
				LGrInt[i] = LGrInt[i + 1];
				LGrInt[i + 1] = b;
			}
		}
	}

	//равномерное распределение
	for (int i = 0; i < NumRanDat; i++) {
		for (int i = 0; i < NumRanDat; i++)
			arr[i] = xmin + rand() % (xmax - xmin);
	}

	res = new unsigned short int[NInt];
	for (int i = 0; i < NInt; i++) {
		res[i] = 0;
	}

	MYASM(arr, LGrInt, res, NInt, NumRanDat);

	cout << "result:\n";
	result << "result:\n";
	cout << "№\tЛев.Гр.\tКол-во чисел" << endl;
	result << "№\tЛев.Гр.\tКол-во чисел" << endl;
	for (int i = 0; i < NInt; i++) {
		cout << i + 1 << '\t' << LGrInt[NInt - 1 - i] << '\t' << res[NInt - 1 - i] << endl;
		result << i + 1 << '\t' << LGrInt[NInt - 1 - i] << '\t' << res[NInt - 1 - i] << endl;
	}
	cout << endl << endl;

	//сортировка сгенерированных чисел (для проверки)
	for (int j = 0; j < NumRanDat - 1; j++) {
		for (int i = 0; i < NumRanDat - j - 1; i++) {
			if (arr[i] > arr[i + 1]) {
				int b = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = b;
			}
		}
	}

	/*cout << "Сгенерированные числа: ";
	for (int q = 0; q < NumRanDat; q++){
	cout << arr[q] << " ";
	}*/

	cin.clear();
	cin.sync();
	cin.get();
	result.close();
	delete[] arr;
	delete[] LGrInt;
	delete[] res;
	return 0;
}
