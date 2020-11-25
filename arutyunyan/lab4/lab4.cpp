#include <iostream>

const int MAXSIZE = 80;


char* MakeString(char* input_str) {
    char* out_str = new char[MAXSIZE + 1];

    asm(".intel_syntax noprefix\n\t"
        "mov rsi, %1\n"         // адрес начала строки-источника
        "mov rdi, %0\n"         // адрес начала строки-приемника

        "char_loop:\n"          // цикл по всем символам
            "mov al, [rsi]\n"   // извлекаем очередной символ"
            
            "cmp al, 0\n"       // если конец строки
            "je exit\n"         // то закругляемся

            "inc rsi\n"         // передвигаем указатель на текущий символ

        "handle_char:\n"        // здесь проверяем, является ли символ подходящим
            "cmp al, 48\n"    
            "jb char_loop\n"    // если символ имеет код меньше 30 (за символом 0)

        "digit:\n"
            "cmp al, 57\n"
            "jbe write_char\n"  // если цифра, то просто записываем ее

            // иначе символ может быть символом

        "cyr_char:\n"
            "cmp al, 128\n"
            "jb char_loop\n"    // если код символа находится за буквой А
            "cmp al, 239\n"
            "jg char_loop\n"    // если код символа находится после буквы я
            
            // иначе символ является буквой кириллицы => просто записываем ее в выход

        "write_char:\n"
            "mov [rdi], al\n"
            "inc rdi\n"

            "jmp char_loop\n"

        "exit:\n"
        : "=m"(out_str)
        : "m"(input_str)
    );

    return out_str;
}

int main() {
    std::cout << "Арутюнян Самвел, группа 9383, вариант 1\n"
              << "Формирование выходной строки только из цифр "
                 "и русских букв входной строки" << std::endl;

    char input_str[MAXSIZE + 1] = {0};
    std::cin >> input_str;
    input_str[MAXSIZE] = 0;

    char* answer = MakeString(input_str);

    std::cout << "Результат: " << answer << std::endl;
    delete[] answer;
    return 0;
}