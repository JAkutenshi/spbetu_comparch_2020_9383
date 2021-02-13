.686
.MODEL FLAT, C
.STACK
.DATA
.CODE
func PROC C NumRanDat:dword, arr:dword, LGrInt:dword, ans:dword, NInt:dword

	mov ecx, 0					;������� ��� ������� �� LGrInt (j)
	mov eax, [arr] 
	mov esi, [LGrInt] 
	mov edi, [ans] 
	mov ebx, 0					;������� ��� ������� �� arr (i)

MainLoop:
    cmp ecx, NInt				;j < NInt [LGrInt]
    je lastint
	cmp ebx, NumRanDat
	je done
	push ebx
	shl ebx, 2
    mov edx, [eax + ebx]		;edx = arr[i]
	pop ebx

	push ecx
	shl ecx, 2
	push eax
	mov eax, [esi + ecx]		;eax = LGrInt[j]
	cmp edx, eax				;���������� arr[i] � LGrInt[j]
	pop eax
	pop ecx
compare:
	jl append					;���� arr[i] < LGrInt[j], �� ans[j]++
next:
	inc ecx						;j++
	jmp MainLoop
append:
	push ecx
	shl ecx, 2
	push eax
	mov eax, [edi + ecx]		;eax = ans[j]
	add eax, 1					
	mov [edi + ecx], eax		;ans[j]++
	pop eax
	pop ecx
LoopDone:
	inc ebx						;i++
    jmp MainLoop
    

lastint:
	push ecx
	shl ecx, 2
	push eax
	mov eax, NumRanDat		;eax = ans[j]
	sub eax, ebx					
	mov [edi + ecx], eax		;ans[j]++
	pop eax
	pop ecx
done:
	ret
func ENDP

END 