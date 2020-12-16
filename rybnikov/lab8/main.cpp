// Asin
// usage double Asin(double *xP)
// math.h
// asin(x) = atan( x/ sqrt(1 - x^2))
//#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
//#include <cmath>
#include <iomanip>


using namespace std;

double Asin(double *xP){
    double x = *xP;
    double y;
    __asm{
        fld x;          // в стеке х
        fld x;          // в стеке х х
        fmul;           // в стеке x^2
        fld1;           // добавили 1, в стеке 1 и х^2
        fxch st(1);     // поменяли местами значения: в стеке х**х и 1
        fsub;           // вычли единицу первый элемент стека: в стеке - 1 х**х
        fsqrt;          // из оставшегося вычли корень
        fld x;          // в стеке х и корень
        fxch st(1);     // в стеке корень и х
        fdiv;           // поделили второй на первый элемент в стеке: в стеке (х делить на корень)
        fld1;           // добавили 1 в стек. в стеке 1 и (х делить на корень)
        fpatan;         // вычли арктангенс: поделили (...) на 1
        fstp y;         // достали из стека значение
        
    exit:
    }
    
    return y;
}

int main() {

    double x;
    cout << "Insert the number" << endl;
    cin >> x;
    cout << endl;

    while (x < -1 || x > 1) {
        cout << "[-1;1]......" << endl;
        cout << "Insert the number" << endl;
        cin >> x;
        cout << endl;
    }

    cout << "Original asin: " << setprecision(10) << asin(x) << endl;
    cout << "Twin asin: " << setprecision(10) << Asin(&x) << endl;

    return 0;
}
