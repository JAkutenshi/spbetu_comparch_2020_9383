#include <iostream>
#include <math.h>

using namespace std;

double Acos(double* xP)
{
	double x = *xP;
	double result = 0;
	_asm
	{
		fld x; //st(0) = x
		fld st(0); //st(0) = x; st(1) = x
		fmul; //st(0) = x^2;
		fld1; //st(0) = 1; st(1) = x^2;
		fxch st(1); //st(0) = x^2; st(1) = 1;
		fsub; //st(0) = 1-x^2
		fsqrt; //st(0) = sqrt(1-x^2)
		fld x; //st(0) = x; st(1) = sqrt(1-x^2)
		fpatan; //st(0) = atan(sqrt(1-x^2)/x)
		fstp result;
	}
	return result;
}



int main()
{
	double x;

	cout<< "Введите x в диапазоне [-1; 1]: ";
	cin>> x;
	if ((x < -1) || (x > 1))
	{
		cout<< "x вне диапазона!" << '\n';
	}

	cout << "C++ arccos = "<< acos(x) << '\n';
	cout << "Assembly arccos = "<< Acos(&x) << '\n';

	return 0;
}
