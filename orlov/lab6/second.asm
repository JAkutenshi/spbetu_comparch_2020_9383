.586p
.MODEL flat, C
.DATA
.CODE

PUBLIC C second
second PROC C result: dword, lenresult: dword, leftborders: dword, nint: dword, minx: dword, maxx: dword, output: dword

    push esi
    push edi
    push ebp

    mov esi, leftborders
    mov ecx, nint 
    mov eax, 0

filoop:
    mov eax, [esi]
    sub eax, minx
    mov [esi], eax
    mov esi, 4

loop filoop

mov edi, result
mov ecx, nint
mov esi, leftborders
sub ebx, ebx
mov eax, [esi]

sloop:

    push ecx
    mov ecx, eax
    push esi
    mov esi, output 

    tloop:

        mov eax, [edi]
        add [esi+4*ebx], eax
        add edi, 4
        
    loop tloop

    pop esi

    mov eax, [esi]
    add esi, 4
    sub eax, [esi]
    neg eax

    inc ebx
    pop ecx
loop sloop

mov esi, output 
mov ecx, nint
sub eax, eax

foloop:

    add eax, [esi]
    add esi, 4
    
loop foloop

mov esi, output
sub eax, lenresult 
neg eax
add [esi+4*ebx], eax

pop ebp
pop edi
pop esi

second ENDP
END