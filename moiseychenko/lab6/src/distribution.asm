.model flat,c

.code
distribution proc C arr: dword, LGrInt: dword, NumRanDat: dword, result: dword

	
	mov ebx, [arr]
	mov esi, [LGrInt]
	mov edi, [result]
	mov ecx, [NumRanDat]

	my_loop:
		mov eax, [ebx] ; eax = current_arr
		add ebx, 4 ; ebx = next_arr

	comparison:
		cmp eax, [esi+4]
		jge next_LGrInt ; if current_arr >= next_LGrInt

		; if current_arr < next_LGrInt: current_result++
		mov eax, [edi]
		add eax, 1
		mov [edi], eax
		jmp loop_end

	next_LGrInt:
		add esi, 4 ; esi = next_LGrInt
		add edi, 4 ; edi = next_result
		jmp comparison ; repeat comparison with the next LGrInt

	loop_end:
		dec ecx
		cmp ecx, 0
		jne my_loop

	ret

distribution endp
end