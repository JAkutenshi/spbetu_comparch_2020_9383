.586p
.MODEL FLAT, C
.CODE
PUBLIC C mod1
mod1 PROC C array_mod1: DWORD, NumArray: DWORD, NumRanDat: DWORD, Xmin: DWORD

push esi
push edi

mov edi, NumArray ;������ �����
mov ecx, NumRanDat ;����� ����� �������
mov esi, array_mod1 ;������ �� �����

for_NumRanDat:
    mov eax, [edi] ;������ ������� ������� �����
    sub eax, Xmin ;�������� ������ ��������� �������
    mov ebx, [esi + 4*eax] ;������ �������� �� ����� ������� �� ��������� �������
    inc ebx ;++
    mov [esi + 4*eax], ebx ;������ �������
    add edi, 4 ;��������� �������
    loop for_NumRanDat

pop edi
pop esi

ret
mod1 ENDP
END