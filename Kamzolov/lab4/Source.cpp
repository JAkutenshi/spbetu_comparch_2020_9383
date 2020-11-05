#include "iostream"
#include <stdio.h>
#include <fstream>
#define N 80

using namespace std;

void initialization()
{
	cout << ".....................................................\n";
	cout << ". ��� ��������������: �������������� ���� ��������� .\n"
		<< ". ��������� ���� ������� ������ � ��������, �       .\n"
		<< ". ������������ ���� � ���������, ���������          .\n"
		<< ". ������� ������� ������ ���������� �               .\n"
		<< ". �������� ������ ���������������.                  .\n";
	cout << ". ���������� �������� ������, ������� ������ 9383   .\n";
	cout << ".....................................................\n";
}


int main()
{
	setlocale(0, "");
	initialization();
	char str[N+1];
	cout << "������� ������\n";
	char c;
	cin.getline(str, N);
	char str_out[N * 2 + 1];
	_asm {
		sub eax, eax; eax = 0
		sub esi, esi; esi = 0
		lea edi, str; edi ��������� �� ������ str
		mov ecx, 80; ������� - 80
		f1:
		mov al, [edi]; ��������� ������� ������ str �� ������� edi � al
			cmp al, 'Z'; ���� ������ ��� Z, �� ������ ������ ������ � �������� ������
			jg writeOut
			cmp al, 'A'; ���� ������ ��� A, �� ���� ��������� �� ������������ �����
			jl octalCheck
			add al, 0x20; ��������� � ������ �������
			jmp writeOut
		OctalCheck:
			cmp al, 0x30; ���� ������ ��� 0, �� ������ ������ ������ � �������� ������
			jl writeOut
			cmp al, 0x37; ���� ������ ��� 7, �� ������ ������ ������ � �������� ������
			jg writeOut
			sub al, 0x30; �������� 30, ����� �������� �����
			xor al, 0x7; ����������� 3 ����
			add al, 0x30; ��������� 30, ����� �������� ������
		writeOut:
			mov str_out[esi], al; �������� ������� ������ � �������� ������
			cmp al, 0; ���� ������� ������, �� ����������� ��������� ��� ����������
			je f_end
			inc edi; ����������� �������
			inc esi
			jmp f1; ������������ � ������
		f_end:	
	}
	cout << str_out;
	ofstream file;
	file.open("out.txt");
	file << str_out;
	file.close();
	return 0;
}

