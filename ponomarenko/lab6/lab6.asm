.686
.MODEL FLAT, C
.DATA
elem DW 0
.CODE

ASM_MOD PROC C
    mov eax, [esp+4] ; arr
    mov ebx, [esp+8] ; res
    mov edx, [esp+12] ; LGrInt
    mov edi, [esp+16] ; NInt
    mov ecx, [esp+20] ; NumRanDat
    mov ecx, 0 ; and ecx, 0000FFFFH (обнуляем верхние биты счетчиков с помощью команды умножения)
    mov edi, 0 ; and edi, 0000FFFFH 

f_1:
    push bx ; ebx
    mov bx, [eax]
    mov elem, bx
    pop bx
    
    mov esi, 0 ; индекс результирующего массива
    push ecx
    mov ecx, edi
    
f_2: ; внутренний цикл
    push edx
    mov dx, [edx+esi]
    cmp elem, dx
    jge f_3
    add esi, 2
    pop edx
    loop f_2 ; пока cx не будет равен 0, то есть пока не закончится массив чисел
    
f_3: ; внешний цикл. увеличивает кол-во попавших в диапазон чисел
    mov dx, [ebx+esi]
    inc dx
    mov [ebx+esi], dx
    pop edx
    pop ecx
    add eax, 2
    loop f_1
    
ret
    
ASM_MOD ENDP
END
    
    
    
