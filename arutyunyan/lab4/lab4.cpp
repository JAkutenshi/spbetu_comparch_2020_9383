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

            "inc rsi\n"

            "cmp al, 0x80\n"
            "jb digit\n"    // если код символа имеет ненулевой восьмой бит
            "jge cyr_char\n"

        "digit:\n"
            "cmp al, 0x30\n"
            "jb char_loop\n"
            "cmp al, 0x39\n"
            "jbe write_digit\n"
            "jmp char_loop\n"

        "cyr_char:\n"
            "mov ah, al\n"
            "mov al, [rsi]\n"
            "inc rsi\n"
            "cmp ax, 0xd090\n"
            "jb char_loop\n"
            "cmp ax, 0xd18f\n"
            "jg char_loop\n"
            "xchg ah, al\n"

            // иначе просто записываем символ в выход

        "write_cyr:\n"
            "mov [rdi], ax\n"
            "inc rdi\n"
            "inc rdi\n"
            "jmp char_loop\n"

        "write_digit:\n"
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