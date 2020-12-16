#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <time.h>
#include <locale.h>

using namespace std;


extern "C" void func(int* result, int* LGrInt, int* randoms, int NumRanDat);

template <typename T>
void ReadWithWelcome(T& var, const std::string& message) {
	std::cout << message; std::cin >> var;
}

void main() {
	setlocale(LC_ALL, "RUS");
	srand(time(nullptr));

	int NumRanDat;
	ReadWithWelcome(NumRanDat, "Количество чисел: ");

	int Xmin, Xmax;
	ReadWithWelcome(Xmin, "Левая граница чисел: ");
	ReadWithWelcome(Xmax, "Правая граница чисел: ");

	int NInt;
	ReadWithWelcome(NInt, "Количество интервалов: ");

	auto LGrInt = new int[NInt + 2];
	LGrInt[0] = Xmin;
	for (int i = 1; i < NInt + 1; ++i) {
		ReadWithWelcome(LGrInt[i], "Левая граница #" + std::to_string(i) + ": ");
	}
	LGrInt[NInt + 1] = Xmax;
	std::sort(LGrInt, LGrInt + NInt + 1);

	auto randoms = new int[NumRanDat];
	std::for_each(
		randoms, randoms + NumRanDat,
		[Xmin, Xmax](int& element) {
			element = Xmin + rand() % (Xmax - Xmin + 1);
		}
	);
	std::sort(randoms, randoms + NumRanDat);

	auto result = new int[NInt];
	std::fill(result, result + NInt, 0);

	std::cout << "Массив рандомных чисел:" << std::endl;
	for (int i = 0; i < NumRanDat; ++i) {
		std::cout << randoms[i] << " ";
	} std::cout << std::endl;


	func(result, LGrInt, randoms, NumRanDat);


	for (int i = 0; i < NInt; ++i) {
		if (i == 0)
			std::cout << "Граница [";
		else
			std::cout << "Граница (";
			
		std::cout << std::to_string(LGrInt[i]) << ", "
			<< std::to_string(LGrInt[i + 1]) << "]: "
			<< result[i] << std::endl;
	}
}
