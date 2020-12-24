.686
.MODEL flat, C
.DATA
.CODE
PUBLIC C unit
unit PROC C result1: dword, randDataArr: dword, NumRanDat: dword, Xmin: dword

    push esi
    push edi
    push ebp

    mov edi, result1 
    mov esi, randDataArr 
    mov ecx, NumRanDat 
    mov eax, Xmin

    for_loop:

        mov ebx, [esi]
        sub ebx, eax
        mov ebp, [edi + 4*ebx]
        inc ebp
        mov [edi + 4*ebx], ebp
        add esi, 4

    loop for_loop

    pop ebp
    pop edi
    pop esi

    ret

unit ENDP
END 
