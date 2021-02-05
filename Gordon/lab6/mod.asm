.MODEL FLAT, C
.CODE
func PROC C NumRanDat:dword, arr:dword, LGrInt:dword, ans:dword

	mov ecx,0 			;счетчик для прохода по массиву
	mov ebx,arr 
	mov esi,LGrInt 
	mov edi,ans

main:
	mov edx,[ebx] 		;берем элемент входного массива
	push ebx 			; сохраняем указатель на текущий элемент
	sub ebx,ebx 		; обнуляем указатель

compare:
	mov eax,ebx 		; eax содержит текущий индекс массива границ
	shl eax,2 			; j >> 2
	cmp edx,[esi+eax] 	; сравниваем arr[i] (edx отвечает за перемещение) и LGrInt[j] (esi -> LGrInt, eax = j)
	jle append				; arr[i] <= LGrInt[j]
	inc ebx				; arr[i] > LGrInt[j] => i++
	jmp compare			; проверяем arr[i]

append:
	add eax,edi 		;edi -> ans => eax -> ans
	mov edx,[eax]		
	inc edx				
	mov [eax],edx		 
	pop ebx 			;забираем текущий элемент и ссылаемся на новый
	add ebx,4
	inc ecx 			;i++
	cmp ecx, NumRanDat	
	jl main				;i < NumRanDat

ret
func ENDP

END