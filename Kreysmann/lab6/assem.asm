.Model flat,c

.data
tempI dw 0	;для элементов массива randArray
.code
funcMasm proc C 
	mov  eax,[esp+4] ; result в eax
	mov  ebx,[esp+8] ; LGrInt в ebx	
	mov  edx,[esp+12]; randArray в edx
	mov  di, [esp+16] ; NInt в di
	mov  cx, [esp+20] ; NumRanDat в cx
	and ecx,0000ffffh
	and edi,0000ffffh

	metka1:
		push ax	
		mov ax,[edx]
		mov tempI,ax	;в tempI - текущее число из randArray
		pop ax

		mov esi,0		; индекс для массивов LGrInt и result
		push ecx		; сохраняем счетчик для внешнего цикла
		mov ecx,edi		; в ecx - счетчик для внутреннего цикла
		metka2:
			push ebx	
			mov bx,[ebx+esi] ;в bx - текущий элемент из LGrInt
			cmp tempI,bx	 ;сравневаем очередную левую границу с очередным случайным числом
			jge metka3		 ;если число больше границы, то оно входит в интервал
			add esi,2	 ;прибавляем к индексу массива LGrInt 2
			pop ebx		
		loop metka2			 ;продвигаемся дальше по внутреннему циклу
		metka3:				 
			mov bx, [eax+esi] ;получаем элемент из result
			inc bx			  ;увеличиваем его на 1 
			mov [eax+esi],bx  ;зааносим обратно в result
			pop ebx	 
			pop ecx			  ;в ecx счетчик для внешнего цикла
			add edx,2			 ;прибавляем к индекусу массива randArray 2
	loop metka1 
	
	ret
funcMasm endp
end