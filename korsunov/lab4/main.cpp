#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

void table()
{
    cout << "---------------------------------------------------------\n";
    cout << "|Вид преобразования:                                    |\n";
    cout << "|6. Инвертирование введенных во входной строке цифр     |\n";
    cout << "|в десятичной системе счисления (СС) и преобразование   |\n";
    cout << "|строчных русских букв в заглавные, остальные символы   |\n";
    cout << "|входной строки передаются                              |\n";
    cout << "|в выходную строку непосредственно.                     |\n";
    cout << "|Автор: Корсунов Антон                                  |\n";
    cout << "---------------------------------------------------------\n";
}

char* change(char* arr)
{
    char* arr_ready = new char[80];
    asm
    (
        "mov  %0, %%rsi\n\t"
        "mov  %1, %%rdi\n\t"
        "mov $80, %%ecx\n\t"

        "f1:"
        "lodsb (%%rsi)\n\t" //загружаем символ в al
        "cmpb $0x30, %%al\n\t"//сравниваем символ с кодом цифры 0
        "jl f2\n\t"      //если меньше, то не цифра , идем дальше к проверке на буквы
        "cmpb $0x39, %%al\n\t" //сравниваем символ с кодом цифры 9
        "jg f2\n\t"       //Если больше то не цифра в 10 сс идем к проверке на буквы
        "neg %%al\n\t"
        "add $0x69, %%al\n\t"
        "jmp f_read\n\t"

        "f2:"
        "cmpb $0xB8, %%al\n\t"
        "jne f3\n\t"
        "mov $0xA8, %%al\n\t"
        "jmp f_read\n\t"

        "f3:"
        "cmpb $0xE0, %%al\n\t"
        "jl f_read\n\t"
        "cmpb $0xFF, %%al\n\t"
        "jg f_read\n\t"
        "sub $0x20, %%al\n\t" //получаем строчную букву

        "f_read:"
        "stosb (%%rdi)\n\t"       //записываем символ в выходную строку
        "loop f1\n\t"         //возвращаемся
        ::"m"(arr),"m"(arr_ready)
    );
    return arr_ready;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char arr[80];
    ofstream print_file("file_out.txt");
    table();
    cout << "\nВведите строку:\n";
    fgets(arr, 80, stdin);
    char* arr_ready = change(arr);
    print_file << arr_ready;
    cout << "\nПреобразованная строка:\t" << arr_ready;
    delete arr_ready;
    return 0;
}
