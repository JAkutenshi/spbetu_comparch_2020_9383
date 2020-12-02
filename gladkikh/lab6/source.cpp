#include <iostream>
#include <fstream>
#include <random>

using namespace std;

extern "C" void asm_mod1(int* numbers, int numbers_size, int* res, int res_xmin);
extern "C" void asm_mod2(int* input, int input_size, int input_xmin, int input_xmax, int* intervals, int intervals_size, int* res_final);


int main() {
	setlocale(0, "Russian");
	srand(time(NULL));
	ofstream result("result.txt");

	int amountNumbers = 0;
	int xmin, xmax;
	int* numbers;
	int* bordersArr;
	int numberOfIntervals;
	int* asm_mod1_res;
	int* asm_mod2_res;

	cout << "Введите количество цифр: ";
	cin >> amountNumbers;
	cout << "Введите xmin и xmax: ";
	cin >> xmin >> xmax;
	cout << "Введите число левых границ: ";
	cin >> numberOfIntervals;

	numbers = new int[amountNumbers];
	bordersArr = new int[numberOfIntervals];

	int len_asm_mod1_res = abs(xmax - xmin) + 1;
	asm_mod1_res = new int[len_asm_mod1_res];
	for (int i = 0; i < len_asm_mod1_res; i++) {
		asm_mod1_res[i] = 0;
	}

	asm_mod2_res = new int[numberOfIntervals + 1];
	for (int i = 0; i < numberOfIntervals + 1; i++) {
		asm_mod2_res[i] = 0;
	}

	cout << "Введите все левые границы: ";
	for (int i = 0; i < numberOfIntervals; i++) {
		cin >> bordersArr[i];
	}


	for (int i = 0; i < amountNumbers; i++) {
		numbers[i] = xmin + rand() % (xmax - xmin);
	}
	cout << '\n';

	cout << "Рандомизированные значения\n";
	result << "Рандомизированные значения\n";
	for (int i = 0; i < amountNumbers; i++) {
		cout << numbers[i] << ' ';
		result << numbers[i] << ' ';
	}
	cout << '\n';
	cout << '\n';
	result << '\n';
	result << '\n';

	cout << "Подсчитаем количество повторений каждого отдельного числа:\n";
	result << "Подсчитаем количество повторений каждого отдельного числа:\n";

	asm_mod1(numbers, amountNumbers, asm_mod1_res, xmin);

	for (int i = 0; i < len_asm_mod1_res; i++) {
		cout << asm_mod1_res[i] << ' ';
		result << asm_mod1_res[i] << ' ';
	}
	cout << '\n';
	cout << '\n';
	result << '\n';
	result << '\n';

	asm_mod2(asm_mod1_res, amountNumbers, xmin, xmax, bordersArr, numberOfIntervals, asm_mod2_res);


	cout << "Результат:\n";
	result << "Результат:\n";
	cout << "№\tЛев.Гр.\tКол-во чисел" << endl;
	result << "№\tЛев.Гр.\tКол-во чисел" << endl;
	cout << "1" << "\t" << xmin << '\t' << asm_mod2_res[0] << endl;
	result << "1" << "\t" << xmin << '\t' << asm_mod2_res[0] << endl;
	for (int i = 0; i < numberOfIntervals; i++) {
		cout << i + 2 << "\t" << bordersArr[i] - xmax << '\t' << asm_mod2_res[i + 1] << endl;
		result << i + 2 << "\t" << bordersArr[i] - xmax << '\t' << asm_mod2_res[i + 1] << endl;
		
	}

	delete[] numbers;
	delete[] bordersArr;
	delete[] asm_mod1_res;
	delete[] asm_mod2_res;
	return 0;
}