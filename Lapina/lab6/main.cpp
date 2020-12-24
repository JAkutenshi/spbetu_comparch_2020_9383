#include <iostream>
#include <random>
#include <fstream>

using namespace std;

extern "C"
{
	void M1(int* resArray, int* arr, int size, int xMin);
	void M2(int* resArray, int resSize, int* leftBoarders,
		int intervalsCount, int xMin, int xMax, int* finalArray);
}

int main()
{
	setlocale(0, "");
	int arraySize;
	cout << "Введите размер массива: ";
	cin >> arraySize;

	int xMin, xMax;
	cout << "Введите минимальное значение: ";
	cin >> xMin;
	cout << "Введите максимальное значение ";
	cin >> xMax;
	if (xMin > xMax)
	{
		cout << "Максимальное значение должно быть больше минимального!\n";
		return 0;
	}
	int intervals;
	cout << "Введите количество интервалов: ";
	cin >> intervals;
	int* leftBoarders = new int[intervals];
	cout << "Введите левые границы:";
	for (int i = 0; i < intervals; i++)
	{
		cin >> leftBoarders[i];
	}
	int* array = new int[arraySize];

	for (int i = 0; i < arraySize; i++)
	{
		array[i] = xMin + rand() % (xMax - xMin + 1);
	}
	int* res1 = new int[abs(xMax - xMin) + 1];
	for (int i = 0; i < abs(xMax - xMin) + 1; i++)
	{
		res1[i] = 0;
	}
	M1(res1, array, arraySize, xMin);
	cout << endl;
	int* finalArray = new int[intervals + 1];
	for (int i = 0; i < intervals + 1; i++) {
		finalArray[i] = 0;
	}
	M2(res1, arraySize, leftBoarders, intervals, xMin, xMax, finalArray);
	ofstream textFile;
	textFile.open("out.txt");
	cout << "Рандомные числа: ";
	textFile << "Рандомные числа: ";
	for (int i = 0; i < arraySize; i++)
	{
		cout << array[i] << " ";
		textFile << array[i] << " ";
	}
	cout << endl;
	textFile << endl;
	cout << "Распределение по единичным интервалам: ";
	textFile << "Распределение по единичным интервалам: ";
	for (int i = 0; i < abs(xMax - xMin) + 1; i++)

	{
		cout << res1[i] << " ";
		textFile << res1[i] << " ";
	}
	cout << endl;
	textFile << endl;
	cout <<" № \t  " << "Левая граница \t" << "Колисество чисел в интервале\n";
	textFile << "Номер интервала " << "Левая граница интервала " << "Кол - во чисел в интервале\n";
	cout << " " << 0 << " \t \t " << xMin << " \t\t " << finalArray[0] << endl;
	textFile << " " << 0 << " \t\t\t\t " << xMin << " \t\t\t\t " << finalArray[0] << endl;
	for (int i = 1; i < intervals + 1; i++)
	{
		cout << " " << i << " \t \t " << leftBoarders[i - 1] + xMin << " \t\t " << finalArray[i] << endl;
		textFile << " " << i << " \t\t\t\t " << leftBoarders[i - 1] + xMin << " \t\t\t\t " << finalArray[i] << endl;
	}
}
