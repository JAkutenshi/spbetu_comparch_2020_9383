#include <iostream>
#include <fstream>

using namespace std;

void start_message() {
    cout << "Вариант №23." << endl
        << "Вид преобразования следующий:" << endl
        << "Преобразование всех строчных латинских букв входной строки в заглавные, а" << endl
        << "шестнадцатиричных цифр в инверсные, остальные символы входной строки передаются в" << endl
        << "выходную строку непосредственно." << endl
        << "Работу выполнил студент группы 9383 Чумак Михаил." << endl;
}

int main() {
    setlocale(0, "");
    start_message();
    char str1[80], str2[80];
    cout << "Введите строку: ";
    cin.getline(str1, 80);
    __asm {
	sub eax, eax; eax = 0
	sub esi, esi; esi = 0
	lea edi, str1; edi указывает на начало str1

	start:
	mov al, [edi]; считываем текущий символ str1 по индексу edi в al
	cmp al, 'z'; если больше чем z,
	jg write; то записываем данные в выходную строку
	cmp al, 'a'; если меньше чем a,
	jl check_hex; то проверяем, является ли число шестнадцатеричным,
	sub al, 0x20; иначе переводим латинскую букву к верхнему регистру
	jmp write; и записываем символ в выходную строку

	check_hex:
	cmp al, 0x30; если меньше чем 0,
	jl write; то записываем символ в выходную строку
	cmp al, 0x46; если больше чем F,
	jg write; то записываем символ в выходную строку
	cmp al, 0x3A; если входим в диапазон цифр 0 - 9,
	jl sub_code_numbers; то вычитаем коды на 0x30
	cmp al, 0x41; если не входим в диапазон A - F,
	jl write; то записываем символ между двумя диапазонами в выходную строку
	sub al, 0x7; вычитаем коды на 0x7 для A - F и далее вычитаем 0x30

	sub_code_numbers:
	sub al, 0x30
	xor al, 0xF

	add_codes:
	add al, 0x30
	cmp al, 0x3A; если встретили цифру
	jl write; то выводим её
	add al, 0x7; иначе это из A - F и прибавляем 0x7

	write:
	mov str2[esi], al; помещаем текущий символ в выходную строку
	cmp al, 0; если был встречен нулевой символ,
	je end_func; то заканчиваем
	inc edi; иначе увеличиваем индексы
	inc esi
	jmp start; и возвращаемся к считыванию строки

	end_func:
    }
    cout << str2;
    ofstream output;
    output.open("out.txt");
    output << str2;
    output.close();
    return 0;
}
