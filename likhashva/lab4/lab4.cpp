#include <iostream>
#include <stdio.h>

#define N 80
using namespace std;


int main()
{
    setlocale(LC_ALL, "Russian");
    cout << " ___________________________________________________________________________________\n";
    cout << "|                                                                                   |\n";
    cout << "|������������ ������ �4. ������� 9                                                  |\n";
    cout << "|��������� ������� ���������, ������ 9383                                           |\n";
    cout << "|�������������� ��������� �� ������� ������ ����������������� ���� � ���������� ��, |\n";
    cout << "|��������� ������� ������� ������ ���������� � �������� ������ ���������������.     |\n";
    cout << "|___________________________________________________________________________________|\n\n";
    cout << "������� ������:\n";

    char str_in[N];
    char str_out[N * 2];
    int i = 0;
    cin.getline(str_in, N);
    _asm {
        sub eax, eax;
        mov al, 0		//al - ������ ����� ������
            mov ecx, N	    //ecx = N
            lea edi, str_in	//edi ��������� �� ������ _str
            repne scas 	//ecx �������� N - str.length (����� ������)
            sub ecx, N 	//ecx = -str.length
            neg ecx		//ecx = str.length
            mov edx, ecx    //edx = ecx
            sub edi, edi 	//edi == 0
            sub esi, esi    //esi == 0

            traverse:   //�����
        mov edi, edx	//edi = edx
            sub edi, ecx	//edi - ��������� �� ��������� ������� � str; ����� ���������� ecx, �� ����������� �� ������� ������, ��� ��� ecx ����������� � ������ ���������

            mov al, str_in[edi]	//al �������� ������� �������


            cmp al, '8'  //���� ����� 8
            je eight8

            cmp al, '9'  //���� ����� 9
            je eight9

            jmp write


            eight8 :     //8 �������� �� 10
        mov str_out[esi], '1'
            inc esi  //������������� �������� � �������� ESI �� 1
            mov str_out[esi], '0'
            inc esi  //������������� �������� � �������� ESI �� 1
            loop traverse //����

            eight9 :     //9 �������� �� 11
        mov str_out[esi], '1'
            inc esi  //������������� �������� � �������� ESI �� 1
            mov str_out[esi], '1'
            inc esi  //������������� �������� � �������� ESI �� 1
            loop traverse  //����


            write :
        mov str_out[esi], al //������� al
            inc esi  //������������� �������� � �������� ESI �� 1
            loop traverse  //����

            mov str_out[esi], 0
    }
    cout << "��������������� ������:\n" << str_out;
    return 0;
}