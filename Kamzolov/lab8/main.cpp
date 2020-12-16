#include "iostream"
#include <stdio.h>
#include <fstream>
#include <math.h>

using namespace std;

double Ldexp(double value, int exp)
{
	double res = 0;

	_asm {
		fild exp;  //fild - работает с интом 
		fld value;  // fld - работает с флоат st(0) = value, st(1) = exp
		fscale;  // fscale = st(0)*2^st(1)
		fstp res;  // res = st(0)
	}
	return res;
}

int main()
{
	setlocale(0, "");
	double value;
	int pow;
	std::cout << "¬ведите число: ";
	std::cin >> value;
	std::cout << "¬ведите степень: ";
	std::cin >> pow;
	
	double ans = Ldexp(value, pow);
	std::cout << "¬аше число * 2^(ваша степень):" << ans;
}

