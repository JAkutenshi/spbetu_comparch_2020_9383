.586p
.MODEL FLAT, C
.CODE
PUBLIC C M1
M1 PROC C RESARRAY:DWORD, ARRAY:DWORD, SIZEARR:DWORD, XMIN:DWORD
PUSH ESI
PUSH EDI;сохранение регистров

PUSH EBP
MOV EDI, RESARRAY
MOV ESI, ARRAY
MOV EAX, XMIN
MOV ECX, SIZEARR
for1:         ;метка для цикла
MOV EBX, [ESI]         ;берем число из массива
SUB EBX, EAX           ;вычитаем минимальное
MOV EBP, [EDI+4*EBX]   ;обращаемся к соответствующей ячейке результирующего массива
INC EBP                ;увеличиваем его на 1
MOV [EDI+4*EBX], EBP   ;и кладем назад 
ADD ESI, 4             ;для перехода к следующему элементу
LOOP for1    ;цикл уменьшает ECX пока не 0
POP EBP
POP EDI
POP ESI
ret
M1 ENDP
END

