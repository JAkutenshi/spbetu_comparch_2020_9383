#include <iostream>
#include <random>
#include <time.h>
#include <fstream>

extern "C"
{
	void MODULE1(int* resArray, int* arr, int size, int xMin);
	void MODULE2(int* resArray, int resSize, int* leftBoarders, int intervalsCount, int xMin, int xMax, int* finalArray);
}
int RandomRandom(int min, int max)
{
	
	return min + rand() % (max - min + 1);
}


int main()
{
	setlocale(0, "");
	srand(time(NULL));
	int arraySize;
	std::cout << "Input array size: ";
	std::cin >> arraySize;
	if (arraySize > 16 * 1024)
	{
		std::cout << "Array size should be < 18*1024\n";
		return 0;
	}

	

	int xMin, xMax;
	std::cout << "Input min array value: ";
	std::cin >> xMin;
	std::cout << "Input max array value: ";
	std::cin >> xMax;
	if (xMin > xMax)
	{
		std::cout << "Max array value should be greater than min array value\n";
		return 0;
	}
	int intervalsCount;
	std::cout << "Input count of intervals: ";
	std::cin >> intervalsCount;
	if (intervalsCount > 24)
	{
		std::cout << "Count of interval should be less than 25\n";
		return 0;
	}
	int* leftBoarders = new int[intervalsCount];
	std::cout << "Input " << intervalsCount << " left boarders: ";
	for (int i = 0; i < intervalsCount; i++)
	{
		std::cin >> leftBoarders[i];
		if (leftBoarders[i] > xMax || leftBoarders[i] < xMin) {
			std::cout << "Boarder is out of range!";
			return 0;
		}
	}
	int* array = new int[arraySize];
	for (int i = 0; i < arraySize; i++)
	{
		array[i] = RandomRandom(xMin, xMax);
	}

	int* res1 = new int[abs(xMax-xMin) + 1];
	for (int i = 0; i < abs(xMax - xMin) + 1; i++)
	{
		res1[i] = 0;
	}

	MODULE1(res1, array, arraySize, xMin);
	std::cout << std::endl;
	int* finalArray = new int[intervalsCount + 1];
	for (int i = 0; i < intervalsCount + 1; i++) {
		finalArray[i] = 0;
	}

	MODULE2(res1, arraySize, leftBoarders, intervalsCount, xMin, xMax, finalArray);

	std::ofstream textFile;
	textFile.open("answer.txt");
	std::cout << "Рандомные числа: ";
	textFile << "Рандомные числа: ";
	for (int i = 0; i < arraySize; i++)
	{
		std::cout << array[i] << " ";
		textFile << array[i] << " ";
	}
	std::cout << std::endl;
	textFile << std::endl;
	std::cout << "Распределение по единичным интервалам: ";
	textFile << "Распределение по единичным интервалам: ";
	for (int i = 0; i < abs(xMax - xMin) + 1; i++)
	{
		std::cout << res1[i] << " ";
		textFile << res1[i] << " ";
	}
	std::cout << std::endl;
	textFile << std::endl;
	std::cout << "Номер интервала      " << "Левая граница интервала     " << "Кол-во чисел в интервале\n";
	textFile << "Номер интервала      " << "Левая граница интервала     " << "Кол-во чисел в интервале\n";
	std::cout << "    " << 0 << "     \t \t     " << xMin << "          \t\t       " << finalArray[0] << std::endl;
	textFile << "    " << 0 << "     \t\t\t\t     " << xMin << "          \t\t\t\t       " << finalArray[0] << std::endl;
 	for (int i = 1; i < intervalsCount + 1; i++)
	{
		std::cout << "    " << i << "    \t \t     " << leftBoarders[i-1] - xMax << "          \t\t       " << finalArray[i] << std::endl;
		textFile <<  "    " << i << "    \t\t\t\t     " << leftBoarders[i - 1] - xMax << "          \t\t\t\t       " << finalArray[i] << std::endl;
	}
	
}
