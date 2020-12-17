#include <iostream>
#include <string>
#include <fstream>

int main()
{
    std::ofstream out;
    out.open("file.txt");
    char* str = new char[80];
    std::cout << "Входная строка:\n";
    std::cin.getline(str, 80);
    char* str_2 = new char[80];
    asm(
	"mov rsi, %0\n" // rsi = *str_2
	"mov rdi, %1\n" // rdi = *str
	
	"start:\n"
	"mov ah, [rdi]\n"
	"cmp ah, 0\n"
	"je break\n"
	"cmp ah, 0x30\n"
	"jge is_digit\n"
	"jmp write\n" 
	
	"is_digit:\n"
	"cmp ah, 0x39\n"
	"jle missing\n"
	"cmp ah, 0x41\n"
	"jge is_latin_big\n"
	"jmp write\n"
	
	"is_latin_big:\n"
	"cmp ah, 0x5A\n"
	"jle missing\n"
	"cmp ah, 0x61\n"
	"jge is_latin_small\n"
	"jmp write\n"
	
	"is_latin_small:\n"
	"cmp ah, 0x7A\n"
	"jle missing\n"
	"jmp write\n"
	
	"missing:\n"
	"inc rdi\n"
	"jmp start\n"
	
	"write:\n"
	"mov [rsi], ah\n"
	"inc rsi\n"
	"inc rdi\n"
	"jmp start\n"
	
	"break:\n"
	
	:"=m"(str_2)
	:"m"(str)
	);
	
    std::cout << "Выходная строка:\n" << str_2 << '\n';
    out << str_2 << '\n';
    out.close();
    std::cout << "Работа студентки группы 9383 Пономаренко Софьи.\n";
    std::cout << "14. Исключение латинских букв и цифр, введенных во входной строке при формировании";
    std::cout << " выходной строки.\n";
    delete[] str;
    delete[] str_2;
    return 0;
}
