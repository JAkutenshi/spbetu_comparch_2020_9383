#include <iostream>
#include <fstream>

using namespace std;

#define N 80


void print_info()
{
    cout << "-------------------------------------------------------------" << '\n';
    cout << "| Программу разработал: Хотяков Евгений, группа 9383        |" << '\n';
    cout << "| Задание: Заменить введенные во входной строке русские     |" << '\n';
	cout << "| буквы на числа, соответствующие их номеру по алфавиту,    |" << '\n';
	cout << "| представленному в шестнадцатиричной СС, остальные символы |" << '\n';
	cout << "| входной строки передать в выходную строку непосредственно |" << '\n';
    cout << "-------------------------------------------------------------" << '\n';
    cout << '\n';
}


char* func(char * str_in){
    char *str_out = new char[N*2+1];
    asm(
        "mov r8, %0\n"
        "mov rdi, %1\n"
    "f:\n"
        "mov al, [rdi]\n" //берем текущий символ
        "inc rdi\n" //сдвигаемся к следующему символу
        "cmp al, 0\n" //проверяем является ли символ концом строки
        "je f_end\n"

        "cmp al, 0x80\n"
        "jb Write\n"

        "mov ah, al\n"
        "mov al, [rdi]\n"
        "inc rdi\n"
        "cmp ax, 0xD18F\n" // > я
        "jg Write2\n"
        "cmp ax, 0xD090\n" // < А
        "jl Write2\n"
        "cmp ax, 0xD0AF\n" // <= Я
        "jle Big_char\n" //заглавные буквы
        
        //строчные буквы
        "cmp ax, 0xD0B9\n" // от а до и
        "jle f1_1_9\n"
        "cmp ax, 0xD0BE\n" //от й до о
        "jle f1_A_F\n"
        "cmp ax, 0xD18F\n" //я
        "je Write_Ya\n"
        "mov bl, 0x31\n" //добавляем '1' в массив
        "mov [r8], bl\n"
        "inc r8\n"
        "cmp ax, 0xD0BF\n" //п
        "je f_pi\n"
        "cmp ax, 0xD188\n" //от р до ш
        "jle f2_1_9\n"
        "cmp ax, 0xD18E\n" //от щ до ю
        "jle f2_A_F\n"

        

    "Big_char:"
        "cmp ax, 0xD098\n" // от А до И
        "jle f1_1_9\n"
        "cmp ax, 0xD09E\n" //от Й до О
        "jle f1_A_F\n"
        "cmp ax, 0xD0AF\n" //Я
        "je Write_Ya\n"
        "mov bl, 0x31\n"
        "mov [r8], bl\n"
        "inc r8\n"
        "cmp ax, 0xD09F\n" //П
        "je f_pi\n"
        "cmp ax, 0xD0A8\n" //от Р до Ш
        "jle f2_1_9\n"
        "cmp ax, 0xD0AE\n" //от Щ до Ю
        "jle f2_A_F\n"


    "f1_1_9:\n"
        "cmp al, 0x98\n"//и
        "jle big_char_1_9\n"
        "sub al, 0x7F\n"
        "jmp Write\n"
        "big_char_1_9:\n"
            "sub al, 0x5F\n"//И
            "jmp Write\n"
    "f1_A_F:\n"
        "cmp al, 0x9E\n" //о
        "jle big_char_A_F\n"
        "sub al, 0x78\n"
        "jmp Write\n"
        "big_char_A_F:\n"
            "sub al, 0x58\n"//О
            "jmp Write\n"

    "f_pi:\n"
        "mov al, 0x30\n" //0
        "jmp Write\n"

    "f2_1_9:\n"
        "cmp al, 0x88\n" //ш
        "jg big_char_1_9_2\n"
        "sub al, 0x4F\n"
        "jmp Write\n"
        "big_char_1_9_2:\n"
            "sub al, 0x6F\n" //Ш
            "jmp Write\n"

    "f2_A_F:\n"
        "cmp al, 0x8E\n"//ю
        "jg big_char_A_F_2\n"
        "sub al, 0x48\n"
        "jmp Write\n"
        "big_char_A_F_2:\n"
            "sub al, 0x68\n" //Ю
            "jmp Write\n"

    "Write_Ya:\n"
        "mov al, 0x32\n" //2
        "mov ah, 0x30\n"//0
    "Write2:\n"
        "mov [r8], al\n" //записываем младший байт
        "xchg al, ah\n" //меняем местам младший и старший байт
        "inc r8\n"
    "Write:\n"
        "mov [r8], al\n" 
        "inc r8\n"
        "jmp f\n"
    "f_end:\n"
        :"=m"(str_out)
        :"m"(str_in)
    );
    return str_out;
}
int main(){
    setlocale(0, "");
    char str_in[N+1];
    print_info();
    fgets(str_in, N, stdin);
    char* str_out = func(str_in);
    cout << str_out;
    ofstream file;
	file.open("out.txt");
	file << str_out;
	file.close();
    delete str_out;
	return 0;
}