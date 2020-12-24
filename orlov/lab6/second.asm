.586p
.MODEL FLAT, C
.CODE
PUBLIC C second
second PROC C array: dword, array_size: dword, xmin: dword, borders: dword, intN: dword, result: dword

push esi
push edi
push ebp

mov edi, array  
mov esi, borders  
mov ecx, intN  


for_borders:  
	mov eax, [esi]   
	sub eax, xmin
	mov [esi], eax
	add esi, 4
	loop for_borders


mov esi, borders
mov ecx, intN
mov ebx, 0
mov eax, [esi]

for_loop:
	push ecx  
	mov ecx, eax 
	push esi  
	mov esi, result 

    for_array:
		cmp ecx, 0 
		je end_for
        mov eax, [edi]
        add [esi + 4*ebx], eax
        add edi, 4
        loop for_array

end_for:
    pop esi
    inc ebx 
	mov eax, [esi]
	add esi, 4
	sub eax, [esi]
	neg eax  
	pop ecx
	loop for_loop

mov esi, result
mov ecx, intN
mov eax, 0

fin_for: 
	add eax, [esi]
	add esi, 4
	loop fin_for

mov esi, result
sub eax, array_size
neg eax

add [esi + 4*ebx], eax

pop ebp
pop edi
pop esi

ret
second ENDP
END