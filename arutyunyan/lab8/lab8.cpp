#include <iostream>
#include <math.h>


double poly(double x, int n, double* c) {
    double result = 0;

    __asm {
        ;  умножаем на n - 1
        mov ecx, n
        sub ecx, 1
        mult_loop:
            dec ecx
            add c, 4
            cmp ecx, 0
            jne mult_loop

        mov ecx, n
        sub ecx, 1
        mov edx, c
        fld [edx]; st(0) = c[n-1]

        add_loop:
            dec ecx

            fld x; st(0) = x, st(1) = result
            fmulp st(1), st

            sub c, 4
            mov edx, c
            fld [edx]
            faddp st(1), st
            
            fst result

            cmp ecx, 0
            jne add_loop
    }

    return result;
}


int main()
{
    double x;
    int n;

    std::cout << "Enter x: ";
    std::cin >> x;
    std::cout << "Enter n: ";
    std::cin >> n;

    std::cout << "Enter " << n << " coefficients: ";
    double* c = new double[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> c[i];
    }

    std::cout << "Answer: " << poly(x, n, c) << std::endl;
}