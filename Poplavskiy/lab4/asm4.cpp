#include <iostream>
#include <stdio.h>

#define N 80
using namespace std;

int main()
{
    system("chcp 1251 > nul");
    char _str[N + 1];
    cout << "��4. ���������� ����, ������� 16.\n";
    char str_out[N * 4];
    int i = 0;
    cin.getline(_str, N);
    _asm {
        sub eax, eax;
        mov al, 0;		in al code of str ending symbol
            mov ecx, N;	    ecx = N
            lea edi, _str;	edi now points at start of _str
            repne scas; 	ecx now contains N - str.length
            sub ecx, N; 	ecx = -str.length
            neg ecx;		ecx = str.length
            mov edx, ecx;    edx = ecx
            sub edi, edi; 	edi == 0
            sub esi, esi;    esi == 0

            traverse:
        mov edi, edx;	edi = edx
            sub edi, ecx;	edi - points at last element in str, when we subtracting ecx we pointing to currentIdx, as ecx decreasing every iteration

            mov al, _str[edi];	al contains currentElement

            cmp al, '�'
            je writeSymbol_1

            cmp al, '�'
            je writeSymbol_2

            cmp al, '�'
            je writeSymbol_3

            cmp al, '�'
            je writeSymbol_4

            cmp al, '�'
            je writeSymbol_5

            cmp al, '�'
            je writeSymbol_6

            cmp al, '�'
            je writeSymbol_7

            cmp al, '�'
            je writeSymbol_8

            cmp al, '�'
            je writeSymbol_9

            cmp al, '�'
            je writeSymbol_10

            cmp al, '�'
            je writeSymbol_11

            cmp al, '�'
            je writeSymbol_12

            cmp al, '�'
            je writeSymbol_13

            cmp al, '�'
            je writeSymbol_14

            cmp al, '�'
            je writeSymbol_15

            cmp al, '�'
            je writeSymbol_16

            cmp al, '�'
            je writeSymbol_17

            cmp al, '�'
            je writeSymbol_18

            cmp al, '�'
            je writeSymbol_19

            cmp al, '�'
            je writeSymbol_20

            cmp al, '�'
            je writeSymbol_21

            cmp al, '�'
            je writeSymbol_22

            cmp al, '�'
            je writeSymbol_23

            cmp al, '�'
            je writeSymbol_24

            cmp al, '�'
            je writeSymbol_25

            cmp al, '�'
            je writeSymbol_26

            cmp al, '�'
            je writeSymbol_27

            cmp al, '�'
            je writeSymbol_28

            cmp al, '�'
            je writeSymbol_29

            cmp al, '�'
            je writeSymbol_30

            cmp al, '�'
            je writeSymbol_31

            cmp al, '�'
            je writeSymbol_32

            cmp al, '�'
            je writeSymbol_33

            jmp writeSymbol

            writeSymbol_1 :
        mov str_out[esi], '�'
            inc esi
            loop traverse

            writeSymbol_2 :
        mov str_out[esi], 'b'
            inc esi
            loop traverse

            writeSymbol_3 :
        mov str_out[esi], 'v'
            inc esi
            loop traverse

            writeSymbol_4 :
        mov str_out[esi], 'g'
            inc esi
            loop traverse

            writeSymbol_5 :
        mov str_out[esi], 'd'
            inc esi
            loop traverse

            writeSymbol_6 :
        mov str_out[esi], 'e'
            inc esi
            loop traverse

            writeSymbol_7 :
        mov str_out[esi], 'J'
            inc esi
            mov str_out[esi], 'e'
            inc esi
            loop traverse

            writeSymbol_8 :
        mov str_out[esi], 'z'
            inc esi
            mov str_out[esi], 'h'
            inc esi
            loop traverse

            writeSymbol_9 :
        mov str_out[esi], 'z'
            inc esi
            loop traverse

            writeSymbol_10 :
        mov str_out[esi], 'i'
            inc esi
            loop traverse

            writeSymbol_11 :
        mov str_out[esi], 'y'
            inc esi
            loop traverse

            writeSymbol_12 :
        mov str_out[esi], 'k'
            inc esi
            loop traverse

            writeSymbol_13 :
        mov str_out[esi], 'l'
            inc esi
            loop traverse

            writeSymbol_14 :
        mov str_out[esi], 'm'
            inc esi
            loop traverse

            writeSymbol_15 :
        mov str_out[esi], 'n'
            inc esi
            loop traverse

            writeSymbol_16 :
        mov str_out[esi], 'o'
            inc esi
            loop traverse

            writeSymbol_17 :
        mov str_out[esi], 'p'
            inc esi
            loop traverse

            writeSymbol_18 :
        mov str_out[esi], 'r'
            inc esi
            loop traverse

            writeSymbol_19 :
        mov str_out[esi], 's'
            inc esi
            loop traverse

            writeSymbol_20 :
        mov str_out[esi], 't'
            inc esi
            loop traverse

            writeSymbol_21 :
        mov str_out[esi], 'u'
            inc esi
            loop traverse

            writeSymbol_22 :
        mov str_out[esi], 'f'
            inc esi
            loop traverse

            writeSymbol_23 :
        mov str_out[esi], 'k'
            inc esi
            mov str_out[esi], 'h'
            inc esi
            loop traverse

            writeSymbol_24 :
        mov str_out[esi], 'c'
            inc esi
            loop traverse

            writeSymbol_25 :
        mov str_out[esi], 'c'
            inc esi
            mov str_out[esi], 'h'
            inc esi
            loop traverse

            writeSymbol_26 :
        mov str_out[esi], 's'
            inc esi
            mov str_out[esi], 'h'
            inc esi
            loop traverse

            writeSymbol_27 :
        mov str_out[esi], 'j'
            inc esi
            mov str_out[esi], 's'
            inc esi
            mov str_out[esi], 'h'
            inc esi
            loop traverse

            writeSymbol_28 :
        mov str_out[esi], 'h'
            inc esi
            mov str_out[esi], 'h'
            inc esi
            loop traverse

            writeSymbol_29 :
        mov str_out[esi], 'i'
            inc esi
            mov str_out[esi], 'h'
            inc esi
            loop traverse

            writeSymbol_30 :
        mov str_out[esi], 'j'
            inc esi
            mov str_out[esi], 'h'
            inc esi
            loop traverse

            writeSymbol_31 :
        mov str_out[esi], 'e'
            inc esi
            mov str_out[esi], 'h'
            inc esi
            loop traverse

            writeSymbol_32 :
        mov str_out[esi], 'j'
            inc esi
            mov str_out[esi], 'u'
            inc esi
            loop traverse

            writeSymbol_33 :
        mov str_out[esi], 'j'
            inc esi
            mov str_out[esi], 'a'
            inc esi
            loop traverse


            writeSymbol :
        mov str_out[esi], al
            inc esi
            loop traverse

            mov str_out[esi], 0
    }
    cout << str_out;
    return 0;
}