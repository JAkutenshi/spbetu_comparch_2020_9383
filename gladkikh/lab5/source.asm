AStack	SEGMENT	STACK
	DB 256 DUP(?)
AStack  ENDS

DATA	SEGMENT
	keep_cs DW 0 ; для хранения сегмента
	keep_ip DW 0 ; и смещения прерывания
DATA      ENDS

CODE    SEGMENT
    ASSUME SS:AStack, DS:DATA, CS:CODE

SUBR_INT PROC FAR ;начало процедуры

	push ax ;сохранение изменяемого регистра
	push dx ;сохранение изменяемого регистра

	mov ah, 2 ;вывод на "дисплей"
	mov dl, 07h ;beep
	int 21h

	pop dx ;восстановление регистра
	pop ax ;восстановление регистра

	mov al, 20h	;разрешаем обработку прерываний
	out 20h, al	;с более низкими уровнями
	iret ;конец прерывания

SUBR_INT ENDP ;конец процедуры

MAIN PROC FAR

	push ds
	sub ax, ax
	push ax
	mov ax, DATA
	mov ds, ax

	mov ah, 35h
	mov al, 1ch
	int 21h
	mov keep_ip, bx
	mov keep_cs, es

	push ds
	mov dx, offset SUBR_INT
	mov ax, seg SUBR_INT
	mov ds, ax
	mov ah, 25h
	mov al, 1ch
	int 21h
	pop ds

	int 1ch


	;восстанавливаем старый вектор прерывания
	cli
	push ds
	mov dx, keep_ip
	mov ax, keep_cs
	mov ds, ax
	mov ah, 25h
	mov al, 1ch
	int 21h
	pop ds
	sti

	ret

MAIN ENDP
CODE ENDS
END MAIN
