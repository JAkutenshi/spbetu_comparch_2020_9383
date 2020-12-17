.686
.MODEL FLAT, C
.STACK
.DATA
.CODE
distribution PROC C arr_length:dword, arr:dword, lower_ranges_arr:dword, range_arr:dword

	mov ecx, 0			;счетчик для прохода по массиву
	mov ebx, [arr] 
	mov esi, [lower_ranges_arr] 
	mov edi, [range_arr] 

f1:
	mov edx, [ebx]		;берем элемент входного массива
	push ebx			;сохраняем указатель на текущий элемент
	sub ebx, ebx		;обнуляем указатель

f2:
	mov eax, ebx		;eax содержит текущий индекс массива границ
	shl eax, 2			;индекс умножаем на 4, так как каждый элемент по 4 байт
	cmp edx, [esi+eax]	;сравниваем текующий элемент с текущей левой границей
	jle fe
	inc ebx
	jmp f2

fe:
	add eax, edi		;после сложения указываем на элемент в результирующем массиве для инкрементирования
	mov edx, [eax]
	inc edx
	mov [eax], edx
	pop ebx				;забираем текущий элемент и ссылаемся на новый
	add ebx, 4
	inc ecx				;инкрементируем индекс массива
	cmp ecx, arr_length
	jl f1

ret
distribution ENDP

END 