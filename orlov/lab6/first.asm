.586p
.MODEL FLAT, C
.CODE
PUBLIC C first
first PROC C array: dword, arraysize: dword, res: dword, xmin: dword

push esi
push edi

mov edi, array  ;исходный массив
mov ecx, arraysize
mov esi, res  ;массив на выход

for_numbers:
	mov eax, [edi]
	sub eax, xmin
	mov ebx, [esi + 4*eax] 
	inc ebx 
	mov [esi + 4*eax], ebx 
	add edi, 4 
	loop for_numbers

pop edi
pop esi

ret
first ENDP
END 