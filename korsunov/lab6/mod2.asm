.586p
.MODEL FLAT, C
.CODE
PUBLIC C mod2
mod2 PROC C array_mod1: DWORD, NumRanDat: DWORD, LGrInt: DWORD, NInt: DWORD, Xmin: DWORD, Xmax: DWORD, array_mod2:DWORD

mov esi, LGrInt    ; ������ ����� ������
mov ecx, NInt ; ���������� ������
mov edx, Xmin ; ����������� ��������

for_LGrInt:   ; �������� ������ �������� ��� ��������� ������� ����������
mov eax, [esi]
sub eax, xmin
mov [esi], eax
add esi, 4
loop for_LGrInt

mov esi, LGrInt ;
mov ecx, NInt  
mov ebx, 0
mov edi, array_mod1           
mov eax, [esi] ; ������� ������� ����� ����������

for2i:
push ecx
mov ecx, eax  ; ����� ��������� ������� ����� ����������
push esi
mov esi, array_mod2

for2j:
mov eax, [edi]  ;   ������� ������� array_mod1
add [esi + ebx*4], eax  
add edi, 4
loop for2j

pop esi        
mov eax, [esi]
add esi, 4
sub eax, [esi]
neg eax

inc ebx   ;��� ��������� � ���������� ��������
pop ecx
loop for2i

mov esi, array_mod2
mov ecx, NInt
mov eax, 0

 for3:            ;��� ������� ���������� ���������
 add eax, [esi]   ;
 add esi, 4
 loop for3
 
sub eax, NumRanDat    ;
neg eax              ;

mov esi, array_mod2

add [esi + 4 * ebx], eax ;

ret
mod2 ENDP
END