#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#define NMAX 80

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
  char* str_out = new char[NMAX];
  asm(
    "mov r8, %0         \n"// r8 = %0
    "mov rdi, %1        \n"// rdi = %1
"getChar:               \n"//==================================================
    "mov al, [rdi]      \n"// al = getChar(rdi)
    "inc rdi            \n"// rdi++
    "cmp al, 0          \n"// if (al == '\0')
    "je exit            \n"// break
    "cmp al, 0x80       \n"// if(с < 0x80)
    "jb Char            \n"// 
"WChar:                 \n"//==================================================
    "mov ah, al         \n"// ah = al
    "mov al, [rdi]      \n"// al = getChar(rdi) // read second byte of wchar
    "inc rdi            \n"// rdi++
    "jmp writeWChar     \n"// print
"Char:                  \n"//==================================================
    "cmp al, 0x5a       \n"// if(c > 'Z')
    "jg writeChar       \n"// print
    "cmp al, 0x30       \n"// if(c < '0')
    "jl writeChar       \n"// print
    "cmp al, 0x41       \n"// if(c < 'A')
    "jl Number          \n"// 
"Lower:                 \n"//==================================================
    "add al, 0x20       \n"// lower(c)
    "jmp writeChar      \n"// print
"Number:                \n"//==================================================
    "cmp al, 0x39       \n"// if(c > '9')
    "jg writeChar       \n"// print
    "neg al             \n"// al = -al           // 0x30 ix '0'
    "add al, 0x69       \n"// 0x69 = 0x39 + 0x30 // 0x39 is '9'
"writeChar:             \n"//==================================================
    "mov [r8], al       \n"// *r8 = c       // 1 byte
    "inc r8             \n"// r8++
    "jmp getChar        \n"// loop
"writeWChar:            \n"//==================================================
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
