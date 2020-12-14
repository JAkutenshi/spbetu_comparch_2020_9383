.586p
.MODEL FLAT, C
.CODE
PUBLIC C mod1
mod1 PROC C array_mod1: DWORD, NumArray: DWORD, NumRanDat: DWORD, Xmin: DWORD

push esi
push edi

mov edi, NumArray ;массив чисел
mov ecx, NumRanDat ;длина этого массива
mov esi, array_mod1 ;массив на выход

for_NumRanDat:
    mov eax, [edi] ;кладем елемент массива чисел
    sub eax, Xmin ;получаем индекс выходного массива
    mov ebx, [esi + 4*eax] ;кладем значение по этому индексу из выходного массива
    inc ebx ;++
    mov [esi + 4*eax], ebx ;кладем обратно
    add edi, 4 ;следующий элемент
    loop for_NumRanDat

pop edi
pop esi

ret
mod1 ENDP
END