.686
.MODEL flat, C
.DATA
.CODE
PUBLIC C single
single PROC C result: dword, arr: dword, lenarr: dword, minx: dword

    push esi
    push edi
    push ebp

    mov edi, result 
    mov esi, arr 
    mov ecx, lenarr 
    mov eax, minx
    

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

single ENDP
END 