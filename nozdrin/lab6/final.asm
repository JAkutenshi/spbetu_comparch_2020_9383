.686
.MODEL flat, C
.DATA
.CODE
PUBLIC C final
final PROC C result1: dword, result_len: dword, LGrInt: dword, NInt: dword, Xmin: dword, Xmax: dword, result2: dword

    push esi
    push edi
    push ebp

    mov esi, LGrInt
    mov edx, Xmin 
    mov ecx, NInt 
    mov eax, 0

    for_loop_1:

        mov eax, [esi]
        add eax, Xmax 
        mov [esi], eax
        mov esi, 4

    loop for_loop_1

    mov edi, result1
    mov ecx, NInt
    mov esi, LGrInt
    sub ebx, ebx
    mov eax, [esi]

    for_loop_2:

        push ecx
        mov ecx, eax
        push esi
        mov esi, result2 

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

    mov esi, result2 
    mov ecx, NInt
    sub eax, eax

    for_loop_4:

        add eax, [esi]
        add esi, 4
    
    loop for_loop_4

    mov esi, result2
    sub eax, result_len 
    neg eax
    add [esi+4*ebx], eax

    pop ebp
    pop edi
    pop esi

final ENDP
END
