.686
.MODEL FLAT, C
.STACK
.DATA
.CODE
func PROC C NumRanDat:dword, arr:dword, LGrInt:dword, ans:dword, NInt:dword

	mov ecx, 0					;счетчик для прохода по LGrInt
	mov eax, [arr] 
	mov esi, [LGrInt] 
	mov edi, [ans] 

outerLoop:

    cmp ecx, NInt				;i < NInt
    je done
    mov ebx, 0					;j

innerLoop:
	push ebx
	shl ebx, 2
    mov edx, [eax + ebx]		;arr[i] -> edx
	pop ebx
	push ecx
	shl ecx, 2

	push eax
	mov eax, [esi + ecx]
	cmp edx, eax				;сравниваем arr[i] и LGrInt[j]

	pop eax

	pop ecx
leftborder:
	jl next						;если arr[i] < LGrInt[j], то след элемент
rightborder:
	push ecx
	shl ecx, 2
	cmp edx, [esi + ecx + 4]	;arr[i] >= LGrInt[j], сравниваем с LGrInt[j+1]
	pop ecx
	jg next						;если arr[i] > LGrInt[j+1], то след элемент
	push ecx
	shl ecx, 2
	push eax
	mov eax, [edi + ecx]
	add eax, 1					;иначе ans[j]++
	mov [edi + ecx], eax
	pop eax
	pop ecx
next:
	inc ebx
    cmp ebx, NumRanDat
    je innerLoopDone
    jmp innerLoop

innerLoopDone:

    inc ecx
    jmp outerLoop

done:
	ret
func ENDP

END 