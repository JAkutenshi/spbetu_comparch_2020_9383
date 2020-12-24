.586p
.MODEL FLAT, C
.CODE
PUBLIC C module_1
module_1 PROC C mass: dword, NumRatDat: dword, mass_after_module1: dword, Xmin: dword

push esi
push edi

mov edi, mass ;исходный массив
mov ecx, NumRatDat  ;размер исходного массива
mov esi, mass_after_module1 ;массив на выход


module_1_work:
    mov eax, [edi]
    sub eax, Xmin
    mov ebx, [esi + 4*eax]
    inc ebx
    mov [esi + 4*eax], ebx
    add edi, 4
    loop module_1_work

pop edi
pop esi

ret
module_1 ENDP
END  