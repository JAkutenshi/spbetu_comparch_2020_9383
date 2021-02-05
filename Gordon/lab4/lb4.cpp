#include <iostream>
#include <fstream>

char* foo(char* src) 
{
    char* newstr = new char[80 + 1];
    newstr[0] = '\0';
    asm(".intel_syntax noprefix\n\t"
        "mov rsi, %1\n"         // адрес начала src
        "mov rdi, %0\n"         // адрес начала newstr

        "char_loop:\n"          // идем по всем символам src
            "mov al, [rsi]\n"   // записываем символ в al

            "cmp al, 0\n"       // сравниваем с 0 терминалом
            "je exit\n"         // если это он, то выходим

            "inc rsi\n"         // след символ

        "handle_char:\n"        // откидываем лишние символы
            "cmp al, 65\n"      // если код символа меньше 'a' (латинской),
            "jb char_loop\n"    // то пропускаем символ
        "latin:\n"
            "cmp al, 122\n"
            "jg russian\n"    // больше 'z' => может русский символ
            "cmp al, 97\n"
            "jb check_latin\n"  // меньше 97 => проверяем нет ли там в промежутке от 90 до 97
            "jmp write_char\n" // остальное подходит
        "check_latin:\n"        // al > 65 и < 97
            "cmp al, 90\n"      // al > 90 и < 97
            "jg char_loop\n"    // это не подходит, значит идем к след символу
            "jmp write_char\n"
        "russian:\n"
            "cmp al, 128\n"
            "jb char_loop\n"    // если код символа находится за буквой А
            "cmp al, 239\n"
            "jg char_loop\n"    // если код символа находится после буквы я

            // все остальное подходит

        "write_char:\n"
            "mov [rdi], al\n"
            "inc rdi\n"

            "jmp char_loop\n"

        "exit:\n"
        : "=m"(newstr)
        : "m"(src)
    );
    return newstr;
}

int main() 
{
    std::cout << "Author: Gordon Dmitry 9383\n";
    std::cout << "Var. 3: only russian and latin letters\n";
    char source[80 + 1] = {'\0'};
    //write(source);
    std::cin.getline(source, 80 + 1);
    char* res = foo(source);
    std::cout << '\n';
    std::cout << "Result: " << res;
    std::ofstream out;
    out.open("res.txt");
    out << res;
    out.close();
    delete[] res;
    int a;
    std::cin >> a;
    return 0;
} 