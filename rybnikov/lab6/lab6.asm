 .MODEL FLAT, C
 .DATA
 elem DW 0
 .CODE

ASSEMBLY_ARR PROC C

	mov  eax,[esp+4] ; result 
	mov  ebx,[esp+8] ; arrLeftInt	
	mov  edx,[esp+12]; array
	mov  edi, [esp+16] ; countInterval
	mov  cx, [esp+20] ; sizeArray 
	
	
	and ecx,0000ffffh	; обнуляем верхние 16 бит (счетчики)
	and edi,0000ffffh

func_1:
	push ax					; запихивает ах в стек
	mov ax, [edx]			; текущий элемент
	mov elem, ax			
	pop ax

	mov esi, 0				; обнулили индекс результирующих массивов
	push ecx
	mov ecx, edi			; счетчик
	
func_2:
	push ebx
	mov bx, [ebx+esi]		; положили элемент из левых границ arrLeftInt
	cmp elem, bx			; сравнили с элементом
	jge func_3				; если больше или равно, то подходит для интервала
	add esi, 2				; увеличиваем индекс на 2
	pop ebx
	loop func_2				; цикл пока не пройдем все текущие интервалы


func_3:
	mov bx, [eax+esi]		; взяли элемент из массива количества элементов
	inc bx
	mov [eax+esi],bx		; увеличиваем кол-во, т.к нашли элемент в границе
	pop ebx					
	pop ecx					; счетчик для func_1
	add edx,2				; сдвигаемся на 2
	loop func_1				; цикл
	

ret

ASSEMBLY_ARR ENDP
END
