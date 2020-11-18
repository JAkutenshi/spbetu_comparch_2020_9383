#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

void table()
{
    cout << "---------------------------------------------------------\n";
    cout << "|��� ��������������:                                    |\n";
    cout << "|6. �������������� ��������� �� ������� ������ ����     |\n";
    cout << "|� ���������� ������� ��������� (��) � ��������������   |\n";
    cout << "|�������� ������� ���� � ���������, ��������� �������   |\n";
    cout << "|������� ������ ����������                              |\n";
    cout << "|� �������� ������ ���������������.                     |\n";
    cout << "|�����: �������� �����                                  |\n";
    cout << "---------------------------------------------------------\n";
}

char* change(char* arr)
{
    char* arr_ready = new char[80];
    asm
    (
        "mov  %0, %%rsi\n\t"
        "mov  %1, %%rdi\n\t"
        "mov $80, %%ecx\n\t"

        "f1:"
        "lodsb (%%rsi)\n\t" //��������� ������ � al
        "cmpb $0x30, %%al\n\t"//���������� ������ � ����� ����� 0
        "jl f2\n\t"      //���� ������, �� �� ����� , ���� ������ � �������� �� �����
        "cmpb $0x39, %%al\n\t" //���������� ������ � ����� ����� 9
        "jg f2\n\t"       //���� ������ �� �� ����� � 10 �� ���� � �������� �� �����
        "neg %%al\n\t"
        "add $0x69, %%al\n\t"
        "jmp f_read\n\t"

        "f2:"
        "cmpb $0xB8, %%al\n\t"
        "jne f3\n\t"
        "mov $0xA8, %%al\n\t"
        "jmp f_read\n\t"

        "f3:"
        "cmpb $0xE0, %%al\n\t"
        "jl f_read\n\t"
        "cmpb $0xFF, %%al\n\t"
        "jg f_read\n\t"
        "sub $0x20, %%al\n\t" //�������� �������� �����

        "f_read:"
        "stosb (%%rdi)\n\t"       //���������� ������ � �������� ������
        "loop f1\n\t"         //������������
        ::"m"(arr),"m"(arr_ready)
    );
    return arr_ready;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char arr[80];
    ofstream print_file("file_out.txt");
    table();
    cout << "\n������� ������:\n";
    fgets(arr, 80, stdin);
    char* arr_ready = change(arr);
    print_file << arr_ready;
    cout << "\n��������������� ������:\t" << arr_ready;
    delete arr_ready;
    return 0;
}
