.586p
.MODEL FLAT, C
.CODE
PUBLIC C asm_mod1
asm_mod1 PROC C numbers: dword, numbers_size: dword, res: dword, res_xmin: dword

push esi
push edi

mov edi, numbers
mov ecx, numbers_size
mov esi, res

for_numbers:
	mov eax, [edi]
	sub eax, res_xmin
	mov ebx, [esi + 4*eax]
	inc ebx
	mov [esi + 4*eax], ebx
	add edi, 4
	loop for_numbers

pop edi
pop esi

ret
asm_mod1 ENDP
END