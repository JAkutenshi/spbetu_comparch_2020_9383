 .MODEL FLAT, C
 .DATA
 item DW 0
 .CODE

AFunc PROC C

	mov  eax,[esp+4]			; res			(к смещению прибавляем одно и тоже число, тк типы данных одинаковые)
	mov  ebx,[esp+8]			; LGrInt	
	mov  edx,[esp+12]			; arr
	mov  edi, [esp+16]			; NInt
	mov  cx, [esp+20]			; NumRanDat 
	
	and ecx,0000ffffh			; обнуляем верхние 16 бит (счетчики)
	and edi,0000ffffh



FirstFunc:

	push ax						; заталкиваем ах в стек
	mov ax, [edx]				; в ах текущий элемент массива из псевдослучайных чисел
	mov item, ax			
	pop ax

	mov esi, 0					; esi - индекс массива res
	push ecx
	mov ecx, edi				; счетчик
	


SecondFunc:

	push ebx

	mov bx, [ebx+esi]			; положили в bx элемент из массива LGrInt (взяли смещение ebx(LGrInt массив) + индекс массива res)
	cmp item, bx				; сравнили элемент с элементом из массива псевдослучайных чисел
	
	jge ThirdFunc				; если больше или равно, то подходит для интервала
	add esi, 2					; увеличиваем индекс на 2
	
	pop ebx
	
	loop SecondFunc				; цикл закончится когда пройдем все интервалы



ThirdFunc:

	mov bx, [eax+esi]			; положили в bx элемент из массива количества элементов (взяли смещение eax(res массив) + индекс res)
	inc bx					
	mov [eax+esi],bx			; увеличиваем кол-во, т.к нашли элемент в границе
	
	pop ebx						; вытаскиваем ebx(LGrInt)
	pop ecx						; счетчик для FirstFunc
	
	add edx,2					; сдвигаемся на 2
	
	loop FirstFunc				; внешний цикл
	

ret

AFunc ENDP
END