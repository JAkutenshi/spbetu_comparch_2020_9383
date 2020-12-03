#include <iostream>
#include <fstream>

#define SIZE 160

using namespace std;

char* strFunc(char* inp)
{
    char* out = new char[SIZE];
    asm(
        "mov r8, %0\n" //записываем в регистр адрес начала выходной строки
        "mov rdi, %1\n" //записываем в регистр адрес начала входной строки

        "for_char:\n"
        "mov al, [rdi]\n" //берем текущий символ
        "inc rdi\n" //сдвигаемся к следующему символу
        "cmp al, 0\n" //узнаем конец строки ли это 
        "je break\n"  //если да, то заканчиваем


        " cmp al, 0x41\n " //сравниваем с символом "A"
        //je - если равно
        " je mA\n"         //если равно
        " cmp al, 0x42\n " //сравниваем с символом "B"
        " je mB\n"         
		" cmp al, 0x43\n " //сравниваем с символом "С"
        " je mС\n"   
		" cmp al, 0x44\n " //сравниваем с символом "D"
        " je mD\n" 
		" cmp al, 0x45\n " //сравниваем с символом "E"
        " je mE\n" 
		" cmp al, 0x46\n " //сравниваем с символом "F"
        " je mF\n"         


        "writeChar:\n"
        "mov [r8], al\n" //записываем в выходную строку символ
        "inc r8\n"
        "jmp for_char\n"

        "mA:\n"
		"mov al, 0x31\n"	    
        "mov [r8], al\n" //записываем в выходную строку символ "1"
        "inc r8\n"
		"mov al, 0x30\n"
        "mov [r8], al\n" //записываем в выходную строку символ "0"
        "inc r8\n"		
        "jmp for_char\n"

	    "mB:\n"
		"mov al, 0x31\n"
	    "mov [r8], al\n" //записываем в выходную строку символ "1"
        "inc r8\n"
		"mov al, 0x31\n"
        "mov [r8], al\n" //записываем в выходную строку символ "1"
        "inc r8\n"		
        "jmp for_char\n"
        
		"mС:\n"
		"mov al, 0x31\n"
	    "mov [r8], al\n" //записываем в выходную строку символ "1"
        "inc r8\n"
		"mov al, 0x32\n"
        "mov [r8], al\n" //записываем в выходную строку символ "2"
        "inc r8\n"		
        "jmp for_char\n"

		"mD:\n"
		"mov al, 0x31\n"
	    "mov [r8], al\n" //записываем в выходную строку символ "1"
        "inc r8\n"
		"mov al, 0x33\n"
        "mov [r8], al\n" //записываем в выходную строку символ "3"
        "inc r8\n"		
        "jmp for_char\n"

		"mE:\n"
		"mov al, 0x31\n"
	    "mov [r8], al\n" //записываем в выходную строку символ "1"
        "inc r8\n"
		"mov al, 0x34\n"
        "mov [r8], al\n" //записываем в выходную строку символ "4"
        "inc r8\n"		
        "jmp for_char\n"

		"mF:\n"
		"mov al, 0x31\n"
	    "mov [r8], al\n" //записываем в выходную строку символ "1"
        "inc r8\n"
		"mov al, 0x35\n"
        "mov [r8], al\n" //записываем в выходную строку символ "5"
        "inc r8\n"		
        "jmp for_char\n"

		"break:\n"
        :"=m"(out)
        :"m"(inp)
	);

    return out;
}

int main(){
    cout << "____________________________________________________________________________________\n";
    cout << "|                                                                                   |\n";
    cout << "|Автор: Лапина Анастасия, вариант 8                                                 |\n";
	cout << "|Преобразование введенных во входной строке шестнадцатиричных цифр в десятичную СС, |\n";
    cout << "|остальные символы входной строки передаются в выходную непосредственно             |\n";
    cout << "|___________________________________________________________________________________|\n";

    int n = SIZE/2;
    char str[n];
    fgets(str, n, stdin);


    char* str2 = strFunc(str);



    ofstream file("out.txt");
    file << str2 << '\n';
    cout << str2 << '\n';
    delete str2;
    return 0;
}
