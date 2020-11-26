EOF EQU '$'

AStack  SEGMENT STACK
    DB 1024 DUP(?)
AStack  ENDS

DATA    SEGMENT
    KEEP_CS DW 0    ;для хранения сегмента вектора прерывания
    KEEP_IP DW 0    ;для хранения смещения вектора прерывания
    message DB 'I am interrupt $'
DATA    ENDS

CODE    SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:AStack

MY_INT PROC FAR

    KEEP_SS DW 0
    KEEP_SP DW 0
    KEEP_AX DW 0
    MY_STACK DW 1024 DUP(?)

    procedure:

    mov KEEP_SP, sp
    mov KEEP_AX, ax
    mov KEEP_SS, ss

    mov sp, OFFSET procedure
    mov bx, SEG MY_STACK
    mov ss, bx
    
    push ax ;сохранение изменяемых регистров
	push dx 

	mov ah,9h ;заносим функцию вывода строки 
	mov dx, offset message ;заносим адрес самой строки
    int 21h ;вызываем прервывание, выводя строку

	pop dx ;восстановление регистров
	pop ax 

    mov sp, KEEP_SP
    mov bx, KEEP_SS
    mov ss, bx
    mov ax, KEEP_AX

	mov al,20h  ;разрешение обработки прерываний 
	out 20h,al  ;с более низкими уровнями

	iret ;выход из прерывания
MY_INT ENDP

MAIN PROC FAR

    mov ax, DATA
    mov ds, ax
    GETVECTOR:      ;сохраняем вектор прерывания
    mov ah, 35h     ;функция получения вектора
    mov al, 08h     ;номер вектора
    int 21h
    mov KEEP_CS, es
    mov KEEP_IP, bx

    SETVECTOR:      ;устанавливаем новый вектор прерывания
    push ds
    mov dx, OFFSET MY_INT
    mov ax, SEG MY_INT
    mov ds, ax
    mov ah, 25h ;функция установки вектора
    mov al, 08h ;номер вектора
    int 21h
    pop ds


    int 08h

    RESTOREVECTOR:  ;восстанавливаем старый вектор прерывания
    cli
    push ds
    mov dx, KEEP_IP
    mov ax, KEEP_CS
    mov ds, ax
    mov ah, 25h ;функция установки вектора
    mov al, 08h ;номер вектора
    int 21h
    pop ds
    sti

    mov ah, 4ch ;завершение программы
    int 21h

MAIN ENDP

CODE ENDS

END MAIN