.586p
.MODEL FLAT, C
.CODE
PUBLIC C module_2
module_2 PROC C mass_after_module1: dword, NumRatDat: dword, mass_after_module2: dword, Xmin: dword, LGrInt: dword, Nint: dword

push esi
push edi

mov edi, mass_after_module1 ;исходный массив
mov ecx, Nint  ;количество интервалов
mov esi, LGrInt ;массив левых границ
mov eax, 0

change_interval:
    mov eax, [esi]
    sub eax, Xmin
    mov [esi], eax
    add esi, 4
    loop change_interval


mov esi, LGrInt ;смещаем на начало массива
mov ecx, Nint ;обновляем счетчик
mov ebx, 0 ;Смещение относительно начала массива
mov eax, [esi];сколько шагов будем делать при первом проходе(берем первый левый конец интервала)

add_1:
    push ecx ;сохраняем счетчик
    mov ecx, eax ;запускаем новый счетчик
    push esi ; сохраняем массив левых границ
    mov esi, mass_after_module2 ;записываем в esi итоговый массив
    add_2:

        cmp ecx, 0 
		je end_for

        mov eax, [edi];записываем текущее значение изначального массива
        add [esi + 4*ebx], eax;прибавляем это значение к количеству элементов на текущем интервале
        add edi, 4 ;переходим на следующий элемент изначального массива
        loop add_2

end_for:
    pop esi
    pop ecx
    inc ebx
    mov eax, [esi];берем текущую левую границу
    add esi, 4;берем следующую левую границу
    sub eax, [esi];вычисляем расстояние между границами
    neg eax; берем модуль расстояния
    loop add_1


;на последнем интервале количество чисел будет равно разности колучества чисел вообще и количества числе, добавленных
mov esi, mass_after_module2
mov ecx, Nint
mov eax, 0

add_3:
	add eax, [esi]
	add esi, 4
	loop add_3

mov esi, mass_after_module2
sub eax, NumRatDat
neg eax

add [esi + 4*ebx], eax

pop edi
pop esi

ret
module_2 ENDP
END 