#include <iostream>
#include <fstream>

#define N 80

using namespace std;

int main() {
	setlocale(0, "");
	cout << "________________________________________________________________________" << endl
		<< "|Version #5.                                                           |" << endl
		<< "|The type of conversion is:                                            |" << endl
		<< "|Convert all lowercase Latin letters of the input string to uppercase, |" << endl
		<< "|and decimal digits to inverse, the remaining characters of the input  |" << endl
		<< "|string are passed directly to the output string.                      |" << endl
		<< "|The work was performed by Anna Karpekina, a student of group 9383.    |" << endl
		<< "|______________________________________________________________________| " << endl;
	char arr[N], res[N];
	cout << "Input string: ";
	cin.getline(arr, N);
	__asm{
	mov edi, 0; 
	mov esi, 0; 

	start:
	mov al, arr[edi]  ; считываем текущий символ str1 по индексу edi в al
	cmp al, 'z'    ; если больше чем z,
	jg write
	cmp al, 'a'    ; если меньше чем a,
	jl check_ten   ; то проверяем, является ли символ цифрой,
	sub al, 0x20   ; иначе переводим латинскую букву к верхнему регистру
	jmp write

	check_ten:
	cmp al, 0x30   ; если меньше чем 0,
	jl write       ; то записываем символ в выходную строку
	cmp al, 0x39   ; если больше чем 9,
	jg write       ; то записываем символ в выходную строку
	mov ah, 0x69   ; записsваем в ah 9
	sub ah, al     ; вычитаем из 9 наше число
	mov al,ah
	jmp write
	

	write:
	mov res[esi], al; помещаем текущий символ в выходную строку
	cmp al, 0        ; если был встречен нулевой символ,
	je end_func      ; то заканчиваем
	inc edi          ; иначе увеличиваем индексы
	inc esi
	jmp start        ; и возвращаемся к считыванию строки

	end_func:
	}
	cout << res;
	ofstream output;
	output.open("out.txt");
	output << res;
	output.close();
	return 0;
}