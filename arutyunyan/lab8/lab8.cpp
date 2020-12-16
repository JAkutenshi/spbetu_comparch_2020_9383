#include <iostream>
#include <math.h>


float poly(float x, int n, float* c) {
    float result = 0;

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
    float x;
    int n;

    std::cout << "Введите x: ";
    std::cin >> x;
    std::cout << "Введите n: ";
    std::cin >> n;

    float c = new float[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> c[i];
    }

    std::cout << "Ответ: " << poly(x, n, c) << std::endl;
}