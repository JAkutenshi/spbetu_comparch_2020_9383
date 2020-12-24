.586p
.MODEL FLAT, C
.CODE
PUBLIC C M2
M2 PROC C RESARRAY:DWORD, SIZEARRAY:DWORD, BOARDERS:DWORD, BOARDERSSIZE:DWORD, XMIN:DWORD, XMAX:DWORD, FINALARRAY:DWORD

MOV ESI, BOARDERS     ;массив границ
MOV ECX, BOARDERSSIZE ;количество границ
MOV EAX, 0            ;индекс результирующего массива
MOV EDX, XMIN         ;минимальное значение

for1:   ;вычитаем из каждого и интервала минимальное
MOV EAX, [ESI]
SUB EAX, XMIN
MOV [ESI], EAX
ADD ESI, 4
loop for1

MOV EDI, RESARRAY       ;массив
MOV ECX, BOARDERSSIZE   ;количество интервалов
MOV ESI, BOARDERS       ;интервалы
MOV EBX, 0
MOV EAX, [ESI]

for2i:
PUSH ECX
MOV ECX, EAX  ;кладем границы и выполняем цикл до нее 
PUSH ESI
MOV ESI, FINALARRAY
    for2j:
    MOV EAX, [EDI]
    ADD [ESI + EBX*4], EAX
    ADD EDI, 4
    loop for2j
POP ESI        
MOV EAX, [ESI]
ADD ESI, 4
SUB EAX, [ESI]
NEG EAX

INC EBX   ;для обращения к следующему элементу FINALARRAY
POP ECX
loop for2i

MOV ESI, FINALARRAY
MOV ECX, BOARDERSSIZE
MOV EAX, 0

 for3:            ;для посчета последнего инрвала
 ADD EAX, [ESI]   ;считаем сумму подсчитанных интегралов
 ADD ESI, 4
 loop for3
 
SUB EAX, SIZEARRAY    ;вычитаем размер массива
NEG EAX               ;меняем знак

MOV ESI, FINALARRAY

ADD [ESI + 4 * EBX], EAX ;записываем последний элемент

ret
M2 ENDP
END
