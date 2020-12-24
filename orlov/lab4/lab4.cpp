#include <iostream>

int main()
{
	
	char* str = new char[80];
    std::cout << "Входная строка:\n";
    std::cin.getline(str, 80);
    char* str_2 = new char[80];
	
    asm(
	"mov rsi, %0\n"
	"mov rdi, %1\n"
	
	"loop:\n"
		"mov ah, [rdi]\n"
		"cmp ah, 0\n"
		"je exit\n"
		
		"cmp ah, 0x30\n"
		"jge is_digit\n"
		
		"jmp write\n" 
	
	
	"is_digit:\n"
		"cmp ah, 0x39\n"
		"jle miss\n"
		
		"cmp ah, 0x41\n"
		"jge is_latin_big\n"
		
		"jmp write\n"
	
	"is_latin_big:\n"
		"cmp ah, 0x5A\n"
		"jle miss\n"
		
		"cmp ah, 0x61\n"
		"jge is_latin_small\n"
		
		"jmp write\n"
	
	"is_latin_small:\n"
		"cmp ah, 0x7A\n"
		"jle miss\n"
		
		"jmp write\n"
	
	"miss:\n"
		"inc rdi\n"
		"jmp loop\n"
	
	"write:\n"
		"mov [rsi], ah\n"
		"inc rsi\n"
		"inc rdi\n"
		"jmp loop\n"
	
	"exit:\n"
	
	:"=m"(str_2)
	:"m"(str)
	);
	
    std::cout << "Орлов Даниил, группа 9383, вариант 14\n"
              << " Исключение латинских букв и цифр, введенных "
              "во входной строке при формировании выходной строки" << std::endl;

    std::cout << "Результат: " << str_2 << std::endl;
	
    delete[] str;
    delete[] str_2;
    return 0;
}