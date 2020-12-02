#include <iostream>
#include <stdio.h>

#define N 80
using namespace std;


int main()
{
    setlocale(LC_ALL, "Russian");
    cout << " ___________________________________________________________________________________\n";
    cout << "|                                                                                   |\n";
    cout << "|Лабораторная работа №4. Вариант 9                                                  |\n";
    cout << "|Выполнила Лихашва Анастасия, группа 9383                                           |\n";
    cout << "|Преобразование введенных во входной строке шестнадцатиричных цифр в десятичную СС, |\n";
    cout << "|остальные символы входной строки передаются в выходную строку непосредственно.     |\n";
    cout << "|___________________________________________________________________________________|\n\n";
    cout << "Введите строку:\n";

    char str_in[N];
    char str_out[N * 2];
    int i = 0;
    cin.getline(str_in, N);
    _asm {
        sub eax, eax;
        mov al, 0		//al - символ конца строки
            mov ecx, N	    //ecx = N
            lea edi, str_in	//edi указывает на начало _str
            repne scas 	//ecx содержит N - str.length (длина строки)
            sub ecx, N 	//ecx = -str.length
            neg ecx		//ecx = str.length
            mov edx, ecx    //edx = ecx
            sub edi, edi 	//edi == 0
            sub esi, esi    //esi == 0

            traverse:   //обход
        mov edi, edx	//edi = edx
            sub edi, ecx	//edi - указывает на последний элемент в str; когда вычитается ecx, то указывается на текущий индекс, так как ecx уменьшается с каждой итерацией

            mov al, str_in[edi]	//al содержит текущий элемент


            cmp al, '8'  //если равен 8
            je eight8

            cmp al, '9'  //если равен 9
            je eight9

            jmp write


            eight8 :     //8 меняется на 10
        mov str_out[esi], '1'
            inc esi  //увеличивается значение в регистре ESI на 1
            mov str_out[esi], '0'
            inc esi  //увеличивается значение в регистре ESI на 1
            loop traverse //цикл

            eight9 :     //9 меняется на 11
        mov str_out[esi], '1'
            inc esi  //увеличивается значение в регистре ESI на 1
            mov str_out[esi], '1'
            inc esi  //увеличивается значение в регистре ESI на 1
            loop traverse  //цикл


            write :
        mov str_out[esi], al //заносим al
            inc esi  //увеличивается значение в регистре ESI на 1
            loop traverse  //цикл

            mov str_out[esi], 0
    }
    cout << "Преобразованная строка:\n" << str_out;
    return 0;
}