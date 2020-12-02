.586p
.MODEL FLAT, C
.CODE
PUBLIC C asm_mod2
asm_mod2 PROC C input: dword, init_size: dword, input_xmin: dword, input_xmax: dword, intervals: dword, intervals_size: dword, res_final: dword

push esi
push edi
push ebp

mov edi, input

mov esi, intervals
mov ecx, intervals_size


align_intervals:
	mov eax, [esi]
	add eax, input_xmax
	mov [esi], eax
	add esi, 4
	loop align_intervals

mov esi, intervals
mov ecx, intervals_size
sub ebx, ebx

mov eax, [esi]

for_loop:
	
	push ecx

	mov ecx, eax
	push esi
	
	mov esi, res_final

    for_input: 
        mov eax, [edi]
        add [esi + 4 * ebx], eax
        add edi, 4
        loop for_input

    pop esi
    inc ebx

	mov eax, [esi]
	add esi, 4
	sub eax, [esi]
	neg eax


	pop ecx

	loop for_loop

mov esi, res_final
mov ecx, intervals_size
sub eax, eax

final_interval:
	add eax, [esi]
	add esi, 4
	loop final_interval

mov esi, res_final
sub eax, init_size
neg eax

add [esi + 4 * ebx], eax

pop ebp
pop edi
pop esi

ret
asm_mod2 ENDP
END