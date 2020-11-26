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
	jmp start
	int_keep_ss DW 0
	int_keep_sp DW 0
	int_keep_ax DW 0
	IntStack DW 16 DUP(?)
start:
	mov int_keep_sp, sp
	mov int_keep_ax, ax
	mov ax, ss
	mov int_keep_ss, ax

	mov ax, int_keep_ax

	mov sp, OFFSET start
   	mov ax, seg IntStack
	mov ss, ax

	push ax ;сохранение изменяемого регистра
	push dx ;сохранение изменяемого регистра

	mov al, 10110110b
	out 43h, al
	mov ax, 880 ; sound pitch
	out 42h, al
	mov al, ah
	out 42h, al
	in al, 61h
	mov ah, al
	or al, 3
	out 61h, al
	sub cx, cx
kill_time:
	loop kill_time
	mov al, ah
	out 61h, al ; turn off

	pop dx ;восстановление регистра
	pop ax ;восстановление регистра

	mov int_keep_ax, ax
    mov sp, int_keep_sp
    mov ax, int_keep_ss
    mov ss, ax
    mov ax, int_keep_ax

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
