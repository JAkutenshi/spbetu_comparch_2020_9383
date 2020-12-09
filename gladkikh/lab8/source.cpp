#include <math.h>
#include <iostream>

double cosh(double x) {

    double res;
    int deg = -13;

    _asm {
        fld x; //st(0) = x
        fabs; //st(0) = |x|

        fild deg; //st(0) = deg st(1) = |x|
        fld1; //st(0) = 1 st(1) = deg st(2) = |x|
        fscale; // st(0) = st(0) * 2 ** deg st(1) = |x|

        fcomip st, st(1); // st(0) = |x|
        fstp st(0); // st is empty

        jl little_x;

        fld x; //st(0) = x
        fldl2e; //st(0) = log2e st(1) = x
        fmul; //st(0) = x * log2e
        fld st; //st(0) = x * log2e st(1) = x * log2e
        frndint; //st(0) = [x * log2e] st(1) = x * log2e
        fsub st(1), st; //st(0) = [x * log2e] st(1) = x * log2e - [x * log2e]
        fxch st(1); //st(0) = x * log2e - [x * log2e] st(1) = [x * log2e]
        f2xm1; //st(0) = 2 ** (x * log2e - [x * log2e]) - 1 st(1) = [x * log2e]
        fld1; //st(0) = 1 st(1) = 2 ** (x * log2e - [x * log2e]) - 1 st(2) = [x * log2e]
        fadd; //st(0) = 2 ** (x * log2e - [x * log2e]) st(1) = [x * log2e]
        fscale; //st(0) = e ** x st(1) = [x * log2e]
        fstp st(1); //st(0) = e ** x

        fld x; //same, but with -x
        fchs;
        fldl2e;
        fmul;
        fld st;
        frndint;
        fsub st(1), st;
        fxch st(1);
        f2xm1;
        fld1;
        fadd;
        fscale;
        fstp st(1);

        fadd;//e ** x + e ** (-x)
        fld1;
        fld1;
        fadd;
        fdiv;//(e ** x + e ** (-x)) / 2

        jmp fin;

    little_x:

        fld1;
        fld x;
        fld x;
        fmul;
        fld1;
        fld1;
        fadd;
        fdiv;
        fadd;
        jmp fin;

    fin:
        fstp res;
    }

    return res;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    double x = 0.0;

    std::cout.precision(17);
    std::cout << "�������  ����� : ";
    std::cin >> x;
    std::cout << "����� : " << cosh(x) << "\n";

    //std::cout << "���� ��� ����� ���������� ����� : x = 2 ** (-13) - 2 ** (-17)\n";
    //x = pow(2, -13) - pow(2, -17);
    //std::cout << x << '\n';
    //std::cout << "����� : " << cosh(x) << "\n";
}
