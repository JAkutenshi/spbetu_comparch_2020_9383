.586p

.MODEL flat, C
.DATA
.CODE

PUBLIC C first
first PROC C res: dword, arr: dword, minx: dword

    push esi
    push edi
    push ebp

    mov edi, res
    mov esi, arr

myloop:

    mov ebx, [esi]        
    sub ebx, minx          
    mov ebp, [edi + 4*ebx]  
    inc ebp                
    mov [edi + 4*ebx], ebp  
    add esi, 4              

    loop myloop

pop ebp
pop edi
pop esi

    ret

first ENDP
END 