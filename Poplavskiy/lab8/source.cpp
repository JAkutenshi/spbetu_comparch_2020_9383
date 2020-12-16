#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
double sqrt(double x, double y)
{
	double z = 0;
	__asm
	{
		FLD x; // команда загрузки в стек // загружает из памяти в вершину стека вещественное число x
		FLD x;
		FMUL; // умножение вещественных чисел
		FLD y; // команда загрузки в стек // загружает из памяти в вершину стека вещественное число y
		FLD y;
		FMUL; // умножение вещественных чисел
		FADD; // сложение вещественных чисел
		FSQRT; // извлечение квадратного корня
		Fstp z; // считать вещественное число из стека

	end:
	}
	return z;
}

int main()
{
	setlocale(LC_CTYPE, "rus");
	double a, b;
	cout << "Введите действительное число x:" << endl;
	cin >> a;
	cout << "Введите действительное число y:" << endl;
	cin >> b;

	cout << "Входные данные x=" << a << "; y=" << b << endl;
	cout << "Выходные данные x=" << sqrt(a, b) << endl;

	system("pause");
	return 0;
}
