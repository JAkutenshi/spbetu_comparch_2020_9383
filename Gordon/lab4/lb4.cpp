#include <iostream>
#include <fstream>

char* foo(char* src) 
{
    char* newstr = new char[80 + 1];
    newstr[0] = '\0';
    asm(".intel_syntax noprefix\n\t"
        "mov rsi, %1\n"         // ����� ������ src
        "mov rdi, %0\n"         // ����� ������ newstr

        "char_loop:\n"          // ���� �� ���� �������� src
            "mov al, [rsi]\n"   // ���������� ������ � al

            "cmp al, 0\n"       // ���������� � 0 ����������
            "je exit\n"         // ���� ��� ��, �� �������

            "cmp al, 122\n"
            "jb latin\n"
            "cmp al, 239\n"
            "jb russian\n"
            "inc rsi\n"
            "jmp char_loop\n"         

        "latin:\n"
            "cmp al, 122\n"
            "jg russian\n"    // ������ 'z' => ����� ������� ������
            "cmp al, 97\n"
            "jb check_latin\n"  // ������ 97 => ��������� ��� �� ��� � ���������� �� 90 �� 97
            "jmp write_char\n" // ��������� ��������
        "check_latin:\n"        // al > 65 � < 97
            "cmp al, 90\n"      // al > 90 � < 97
            "jg char_loop\n"    // ��� �� ��������, ������ ���� � ���� �������
            "jmp write_char\n"
        "russian:\n"
            "cmp al, 128\n"
            "jb char_loop\n"    // ���� ��� ������� ��������� �� ������ �
            "cmp al, 239\n"
            "jg char_loop\n"    // ���� ��� ������� ��������� ����� ����� �

            // ��� ��������� ��������

        "write_char:\n"
            "mov [rdi], al\n"
            "inc rdi\n"
            "inc rsi\n"
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