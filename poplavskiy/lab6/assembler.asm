.MODEL FLAT, C
.CODE
MYASM PROC C
		push esi				
		push edi
		push ebp
	
		mov eax, [esp+16]		;*arr
		mov edx, [esp+20]		;*LGrInt
		mov ebx, [esp+24]		;*res

		mov si, [esp+28]		;NInt
		and esi, 0000ffffh
		mov cx, [esp+32]		;NumRanDat
		and ecx, 0000ffffh
		xor ebp, ebp			;тоже самое что mov ebp,0

	for1:
		push ecx				;убираем итератор первого цикла в стек
		mov cx,si				;заменяем на итератор второго цикла
		mov bp, [eax]			;берем число из arr
		and ebp, 0000ffffh
		xor edi,edi				;тоже самое что mov edi,0

		for2:
			cmp bp, [edx+edi]	;сравниваем число и левую границу
			jge quit			;если число больше, значит входит в интервал
			add edi,2			;переход к след. интервалу (увеличиваем смещение на два, т.к. int - 2 байта)
		loop for2				;в цикле, пока не пройдем по всем интервалам

	quit:						;увеличение кол-ва попаданий в интервал
		push edx				;сохраняем edx в стеке
		mov edx, [ebx+edi]		;берем соответствующее интервалу количество попаданий
		inc edx					;увеличиваем это число на 1
		mov [ebx+edi],edx		;убираем его обратно в массив res
		pop edx					;возвращаем из стека edx
		pop ecx					;возвращаем из стека итератор первого цикла
		add eax,2				;переход к следующему числу
	loop for1					;в цикле пока не пройдем по всем числам
		
		pop ebp
		pop edi
		pop esi

		ret

MYASM ENDP
END
