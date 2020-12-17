.686
.MODEL flat, C
.DATA
.CODE
PUBLIC C multiply
multiply PROC C result: dword, lenresult: dword, leftborders: dword, nint: dword, minx: dword, maxx: dword, res: dword

    push esi
    push edi
    push ebp

    mov esi, leftborders
    mov edx, minx 
    mov ecx, nint 
    mov eax, 0

    for_loop_1:

        mov eax, [esi]
        add eax, maxx 
        mov [esi], eax
        mov esi, 4

    loop for_loop_1

    mov edi, result
    mov ecx, nint
    mov esi, leftborders
    sub ebx, ebx
    mov eax, [esi]

    for_loop_2:

        push ecx
        mov ecx, eax
        push esi
        mov esi, res 

        for_loop_3:

            mov eax, [edi]
            add [esi+4*ebx], eax
            add edi, 4
        
        loop for_loop_3

        pop esi

        mov eax, [esi]
        add esi, 4
        sub eax, [esi]
        neg eax

        inc ebx
        pop ecx

    loop for_loop_2

    mov esi, res 
    mov ecx, nint
    sub eax, eax

    for_loop_4:

        add eax, [esi]
        add esi, 4
    
    loop for_loop_4

    mov esi, res
    sub eax, lenresult 
    neg eax
    add [esi+4*ebx], eax

    pop ebp
    pop edi
    pop esi

multiply ENDP
END