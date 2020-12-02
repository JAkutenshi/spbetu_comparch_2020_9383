#include <iostream>
#include <random>
#include <fstream>
#include <locale>

extern "C"
{
	void funcMasm(short* result,short*LGrInt,short *randArray,short NInt,short NumRanDat);
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(0));

	short NumRanDat;    //длина массива псевдослучайных чисел
	short Xmin, Xmax; //Границы диапазона
	short NInt;		  //количество интервалов
	short* LGrInt;	  //массив левых границ интервалов разбиения
	short* randArray; //массив псевдослучаный чисел
	short* result;    //массив с результатом
	std::ofstream file("res.txt"); //файл с результатом


	std::cout << "Длина массива псевдослучайный чисел (<=16000):";
	std::cin >> NumRanDat;

	std::cout << "\nXmin и Xmax:";
	std::cin >> Xmin >> Xmax;

	std::cout << "\nКоличество интервалов (<=24):";
	std::cin >> NInt;

	std::cout << "Левые границы интервалов:(>=Xmin = " <<Xmin
		<<" ,<Xmax = " << Xmax<<"):"<<"\n";

	LGrInt = new short[NInt];

	for (int i =0; i < NInt; i++)
	{
		std::cout << i + 1 << ":";
		std::cin >> LGrInt[i];
		std::cout << '\n';
	}

	randArray = new short[NumRanDat];
	
	//генерация псевдослучайных чисел
	for (int i = 0; i < NumRanDat; i++)
	{
		randArray[i] = Xmin + rand()%(Xmax - Xmin);
	}

	result = new short[NInt];
	for (int i = 0; i < NInt; i++)
	{
		result[i] = 0;
	}

	funcMasm(result, LGrInt, randArray, NInt, NumRanDat);
		
	for (int i = 0; i < NInt; i++)
	{
		file << i+1 << ":" << " Левая граница " << LGrInt[i] << "; Количество чисел, попавших в интервал: " << result[i] << '\n';
	}
		
	/*for (int i = 0; i < NumRanDat; i++)
	{
		std::cout << randArray[i] << ' ';
	}
	std::cout << '\n';
	for (int i = 0; i < NInt; i++)
	{
		std::cout << result[i] << ' ';
	}
	std::cout << '\n';*/

	delete[] randArray;
	delete[] LGrInt;
	delete[] result;
	file.close();

	return 0;
}