.586p
.MODEL FLAT, C
.CODE
PUBLIC C mod1
mod1 PROC C numbers: dword, numbers_size: dword, result: dword, xmin: dword

push esi
push edi

mov edi, numbers  ;исходный массив
mov ecx, numbers_size  ;размер исходного массива
mov esi, result  ;массив на выход

for_numbers:
	mov eax, [edi] ;берем элемент исходного массива
	sub eax, xmin  ;вычитаем минимум, чтобы получить "индекс" для выходного
	mov ebx, [esi + 4*eax] ;помещаем в bx, то что уже по этому индексу в выходном лежит
	inc ebx ;увеличиваем на 1
	mov [esi + 4*eax], ebx ;помещаем по индексу в выходном
	add edi, 4 ;переходим к следующему элементу
	loop for_numbers

pop edi
pop esi

ret
mod1 ENDP
END 