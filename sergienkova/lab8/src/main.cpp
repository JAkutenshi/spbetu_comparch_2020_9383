// acos(x) = atan(sqrt(1-x*x)/x)

#include <iostream>
#include <cmath>
#include <iomanip>


using namespace std;

double Acos_v2(double *xP) {
	double x = *xP;
	double x1 = 0;

	__asm {
		fld x;				// stack = x(0)
		fld x;				// stack = x(0) x(1)
		fmul;				// stack = x * x(0)
		fld1;				// stack = x * x(0), 1(1)
		fxch st(1);			// меняем местами : stack = 1(0), x* x(1)
		fsub;				// вычитаем из 1 нулевой элемент стэка и вставляем в нулевой элемент, stack = 1 - x*x(0)
		fsqrt;				// stack = sqrt(1 - x*x)(0)
		fld x;				// stack = x(0), sqrt(1 - x*x)(1)
		fdiv;				// делим первый элемент стэка на нулевой. stack = sqrt(1 - x*x) / x
		fld1;				// stack = 1(0), sqrt(1 - x*x)(1)
		fpatan;				// вычисляем арктангенс, от значения при делении первого элемента стэка на нулевой. stack = atg(sqrt(1 - x*x) / x)
		fstp x1;			// вытащили из стэка значение
	
	}

	return x1;
}



int main() {
	double x;

	cout << "Enter x from [-1; 1]" << endl;
	cin >> x;
	while (x < -1 || x > 1) {
		cout << "Error" << endl;
		cin >> x;
		cout << endl;
	}

	cout << "cmath asin = " << setprecision(20) <<  acos(x) << endl;
	cout << "assembly asin = " << setprecision(20) << Acos_v2(&x) << endl;

	return 0;
}