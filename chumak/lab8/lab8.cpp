#include <iostream>

using namespace std;
int main() {
    setlocale(LC_ALL, "Rus");
    double x;
    cout << "Enter the value of x: ";
    cin >> x;
    cout << "The result is " << cosh(x) << endl;
}

double cosh(double x) {
    double result;
    double exp1;
    double exp2;
    int degree = -13; // для вычисления по другой формуле
    _asm {
        fld x;              //st(0) = x
        fabs;               //st(0) = |x|
        fild degree;        //st(0) = -13
                            //st(1) = |x|
        fld1;               //st(0) = 1
                            //st(1) = -13
                            //st(2) = |x|
        fscale;             //st(0) = 1 * 2 ** (|x|)
                            //st(1) = |x|
        fcomip st, st(1);   //st(0) = |x|
        fstp st(0);         //стэк пустой
        jl tiny_x           //если |x| слишком мал, то вычисляем по формуле 1+(x^2)/2

        fld x;              //st(0) = x
        fldl2e;             //st(0) = log2e
                            //st(1) = x
        fmul;               //st(0) = x * log2e
        fld st;             //st(0) = x * log2e
                            //st(1) = x * log2e
        frndint;            //st(0) = [x * log2e]
                            //st(1) = x * log2e
        fsub st(1), st;     //st(0) = [x * log2e]
                            //st(1) = x * log2e - [x * log2e]
        fxch st(1);         //st(0) = x * log2e - [x * log2e]
                            //st(1) = [x * log2e]
        f2xm1;              //st(0) = 2 ** (x * log2e - [x * log2e]) - 1
                            //st(1) = [x * log2e]
        fld1;               //st(0) = 1
                            //st(1) = 2 ^ (x * log2e - [x * log2e]) - 1
                            //st(2) = [x * log2e]
        fadd;               //st(0) = 2 ^ (x * log2e - [x * log2e])
                            //st(1) = [x * log2e]
        fscale;             //st(0) = e ^ x st(1) = [x * log2e]
        fstp exp1;          //st(0) = e ^ x

        fld1;               //st(0) = 1
        fld exp1;           //st(0) = e ^ x
                            //st(1) = 1
        fdiv;               //st(0) = e ^ -x
        fld exp1            //st(0) = e ^ x
                            //st(1) = e ^ -x
        fadd;               //st(0) = e ^ x + e ^ (-x)
        fld1;               //st(0) = 1
                            //st(1) = e ^ x + e ^ (-x)
        fld1;               //st(0) = 1
                            //st(1) = 1
                            //st(2) = e ^ x + e ^ (-x)
        fadd;               //st(0) = 2
                            //st(1) = e ^ x + e ^ (-x)
        fdiv;               //st(0) =  (e ^ x + e ^ (-x)) / 2
        jmp end_func;

    tiny_x:
        fld1;               //st(0) =  1
        fld x;              //st(0) =  x
                            //st(1) =  1
        fld x;              //st(0) =  x
                            //st(1) =  x
                            //st(2) =  1
        fmul;               //st(0) =  x ^ 2
                            //st(1) =  1
        fld1;               //st(0) = 1
                            //st(1) =  x ^ 2
                            //st(2) =  1
        fld1;               //st(0) = 1
                            //st(1) = 1
                            //st(2) =  x ^ 2
                            //st(3) =  1
        fadd;               //st(0) = 2
                            //st(1) =  x ^ 2
                            //st(2) =  1
        fdiv;               //st(0) = (x ^ 2) / 2
                            //st(1) =  1
        fadd;               //st(0) = ((x ^ 2) / 2) + 1
        jmp end_func;
    end_func:
        fstp result;
    }
    return result;
}
