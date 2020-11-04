#include <iostream>
#include <fstream>

#define NMAX 80

void init();
std::string *transform(std::string str);

int main() {
  std::ofstream output("output.txt");
  std::string string;
  std::string *result = nullptr;
  
  init();
  std::getline (std::cin, string);
  string = string.substr(0, NMAX);
  result = transform(string);
  
  std::cout << *result << "\n";
  if(output.is_open()) {
    output << *result << "\n";
    output.close();
  }
  delete result;
  return 0;
}

void init() {
  std::cout << "\\Task 12. Формирование номера введенной латинской буквы \\\n"
               "\\по алфавиту и номера позиции его первого вхождения     \\\n"
               "\\входной во строке и выдача их на экран.                \\\n"
               "\\Author: BasilNozdrin group 9383                        \\\n";
}


std::string *transform(std::string str){
  std::string *result = new std::string("a");
  asm(
    "mov  %0, %%rsi\n\t"
    "mov  %1, %%rdi\n\t"
    "mov  $80,%%ecx\n\t"
    "label1:"
    "lodsb (%%rsi)\n\t" //загружаем символ в al
    "cmpb $0x30,%%al\n\t"//сравниваем символ с кодом цифры 0
    "jl label2\n\t"//если меньше, не цифра, идем к проверке буквы
    "cmpb $0x37,%%al\n\t" //сравниваем символ с кодом цифры 7
    "jg label2\n\t"//Если больше, не цифра в 8cс идем к проверке на буквы
    "sub $0x30,%%al\n\t"//вычитаем 30 чтобы получить цифру
    "xor $0x7,%%al\n\t"//инвертируем последние 3 бита
    "add $0x30,%%al\n\t"//прибавляем 30 чтобы получить код цифры
    "jmp label4\n\t"//переходим к выводу в выходную строку
    "label2:"
    "cmpb $0xc0,%%al\n\t "//сравниваем с символом "А"
    "jl label3\n\t"//если меньше, то к проверке на символ Ё
    "cmpb $0xdf,%%al\n\t"// сравниваем с символом "Я"
    "jg label4\n\t"//если больше, то к выводу в выходную строку
    "add $0x20,%%al\n\t"//получаем строчную букву
    "jmp label4\n\t"//переходим к выводу
    "label3:"
    "cmpb $0xa8,%%al\n\t"//сравниваем с символом Ё
    "jne label4\n\t"//если нет то переходим к выводу
    "mov $0xb8,%%al\n\t"//получаем строчную ё
    "label4:"
    "stosb (%%rdi)\n\t"//записываем символ в выходную строку
    "loop label1\n\t"//возвращаемся
    ::"m"(str),"m"(*result)
    );
    return result;
}
