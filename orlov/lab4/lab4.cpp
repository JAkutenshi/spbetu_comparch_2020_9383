#include <iostream>

const int N = 80;

char* MString(char* str_1)
{
    char* str = new char[N + 1];

    asm(".intel_syntax noprefix\n\t"
        "mov rsi, %1\n"         // адрес начала строки-источника
        "mov rdi, %0\n"         // адрес начала строки-приемника

        "cloop:\n"          // цикл по строке
            "mov al, [rsi]\n"   // берем символ
            "cmp al, 0\n"       // условие конца строки
            "je exit\n"         
            "inc rsi\n"         // передвигаем указатель на текущий символ

           "cmp al, 48\n"
            "jb write_c\n"    // если символ имеет код < 48, то мы его записываем 
            
            "cmp al, 58\n"
            "jb cloop\n"    // если символ имеет код >= 48, но < 58, то мы его пропускаем 
            
            "cmp al, 65\n"
            "jb write_c\n"    // если символ имеет код >= 58, но < 65, то мы его записываем 
            
            "cmp al, 91\n"
            "jb cloop\n"    // если символ имеет код >= 65, но < 91, то мы его пропускаем 
            
            "cmp al, 97\n"
            "jb write_c\n"    // если символ имеет код >= 91, но < 97, то мы его записываем 
            
            "cmp al, 123\n"
            "jb cloop\n"    // если символ имеет код >= 97, но < 123, то мы его пропускаем
            
            "jmp write_c\n"    // если символ имеет код >= 123, то мы его записываем 

        "write_c:\n"
            "mov [rdi], al\n"
            "inc rdi\n"
            "jmp cloop\n"

        "exit:\n"
            : "=m"(str)
            : "m"(str_1)
       );

    return str;
}

int main()
{
    std::cout << "Орлов Даниил, группа 9383, вариант 14\n"
              << " Исключение латинских букв и цифр, введенных "
              "во входной строке при формировании выходной строки" << std::endl;

    char str[N + 1] = {0};
    std::cin >> str;
    str[N] = 0; //счетчик конца

    char* answer = MString(str);

    std::cout << "Результат: " << answer << std::endl;
    delete[] answer;
    return 0;
}
