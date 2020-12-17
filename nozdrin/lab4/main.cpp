#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#define NMAX 80
#define N 80

void init();
std::string readLine();
void save(std::string result);
std::string task(char* str_in);

int main() {
  init();
  std::cout << "Enter line\n";
  auto input = readLine();
  char* str = new char[80];
  strcpy(str, input.data());
  auto result = task(str);
  save(result);
  return 0;
}

void init(){
  setlocale(LC_ALL, "Russian");
  std::cout << "\\Задание: преобразовать все заглавные латинские буквы   \\\n"
               "\\входной строки в строчные, а десятичные цифры в        \\\n"
               "\\инверсные, остальные символы входной строки передаются \\\n"
               "\\во выходную строку непосредственно                     \\\n"
               "\\Author: BasilNozdrin group 9383                        \\\n";
};

std::string readLine(){
  std::string line;
  std::getline(std::cin, line);
  line = line.substr(0, NMAX);
  return line;
};

void save(std::string result){
  std::ofstream output("output.txt");
  std::cout << result << "\n";
  if(output.is_open()) {
    output << result << "\n";
    output.close();
  }
};

std::string task(char* str_in) {
  char* str_out = new char[N];
  asm(
    "mov r8, %0         \n"//записываем в регистр адрес начала выходной строки
    "mov rdi, %1        \n"//записываем в регистр адрес начала входной строки
"getChar:               \n"//=====================================
    "mov al, [rdi]      \n"// al = getChar(rdi)
    "inc rdi            \n"// rdi++
    "cmp al, 0          \n"// if (al == '\0')
    "je exit            \n"// break
    "cmp al, 0x80       \n"// if(с < 0x80)
    "jb Latin           \n"// 
"Cyrillic:              \n"//=====================================
    "mov ah, al         \n"// ah = al
    "mov al, [rdi]      \n"// al = getChar(rdi) // read second byte of wchar
    "inc rdi            \n"// rdi++
    "jmp writeWChar     \n"//                   // but it won't be executed because of this jmp
    "cmp ax, 0xD090     \n"// if(c < 'А')       // this part deCapitalizes Cyrillic too
    "jl writeWChar      \n"// print
    "cmp ax, 0xD0AF     \n"// if(c > 'Я')
    "jg writeWChar      \n"// print
    "cmp ax, 0xD09F     \n"// if(c > 'П')
    "jg Cyrillic2       \n"// 'П' has different offset of lower 'п'
    "add ax, 0x0020     \n"// add offset
    "jmp writeWChar     \n"// print
"Cyrillic2:             \n"//=====================================
    "add ax, 0x00E0     \n"// add offset
    "jmp writeWChar     \n"// print
"Latin:                 \n"//=====================================
    "cmp al, 0x5a       \n"// if(c > 'Z')
    "jg writeChar       \n"// skip
    "cmp al, 0x41       \n"// if(c < 'A')
    "jl doNumber        \n"// doNumber
    "add al, 0x20       \n"// capitalize(c)
    "jmp writeChar      \n"// print
"doNumber:              \n"//=====================================
    "cmp al, 0x30       \n"// if(c < '0')
    "jl writeChar       \n"// skip
    "cmp al, 0x39       \n"// if(c > '9')
    "jg writeChar       \n"// skip
    "neg al             \n"// al = -al        // 
    "add al, 0x39       \n"// al = '9' - al   // al = int (al)  // inversed
    "add al, 0x30       \n"// al = '0' + al   // al = (char) al
"writeChar:             \n"//=====================================
    "mov [r8], al       \n"// *r8 = c       // 1 byte
    "inc r8             \n"// r8++
    "jmp getChar        \n"// loop
"writeWChar:            \n"//=====================================
    "xchg ah, al        \n"// swap(ah, al)
    "mov [r8], ax       \n"// *r8 = c       //  2 bytes
    "inc r8             \n"// r8++
    "inc r8             \n"// r8++
    "jmp getChar        \n"// loop
"exit:                  \n"
    "mov [r8], al       \n"// *r8 = c
    :"=m"(str_out)// %0
    :"m"(str_in)  // %1
  );
  return std::string(str_out);
}
