AStack SEGMENT STACK
	DB 1024 DUP(?)
AStack ENDS

DATA SEGMENT
	keep_cs DW 0			;для хранения сегмента
	keep_ip DW 0			;и смещения прерывания
DATA ENDS

CODE SEGMENT
    ASSUME SS:AStack, DS:DATA, CS:CODE

SUBR_INT PROC FAR
	jmp begin
	int_keep_ss DW 0		;для хранения начальных значений сегмента стэка,
	int_keep_sp DW 0		;указателя на стэк,
	int_keep_ax DW 0		;регистра промежуточных операций
	IntStack DW 16 DUP(?)		;внутренний стэк
begin:
	mov int_keep_sp, sp		;запоминаем
	mov int_keep_ax, ax		;нужные нам
	mov ax, ss			;начальные
	mov int_keep_ss, ax		;регистры
	
	mov ax, int_keep_ax
	mov sp, OFFSET begin
   	mov ax, seg IntStack
	mov ss, ax
	
	push ax			;сохранение
	push dx			;изменяемых регистров
	
	mov al, 10110110b		;устанавливаем режим для
	out 43h, al			;для 2-го канала
	
	mov ax, 300 			;определяем звук с заданной частотой
	
	out 42h, al			;устанавливаем звук
	mov al, ah			;в порт
	out 42h, al			;динамика
	
	in al, 61h			;выбор режима
	mov ah, al			;управления
	or al, 3			;динамиком
	out 61h, al			;включение звука
	sub cx, cx
kill_time:
	loop kill_time
	mov al, ah
	out 61h, al 			;выключение звука
	pop dx				;восстановление регистра dx
	pop ax				;восстановление регистра ax
	mov int_keep_ax, ax
	mov sp, int_keep_sp
	mov ax, int_keep_ss
	mov ss, ax
	mov ax, int_keep_ax
	mov al, 20h			;разрешаем обработку прерываний
	out 20h, al			;с более низкими уровнями
	iret				;конец прерывания

SUBR_INT ENDP

MAIN PROC FAR
	push ds
	sub ax, ax
	push ax
	mov ax, DATA
	mov ds, ax
	
	mov ah, 35h			;получаем вектор прерывания
	mov al, 08h
	int 21h
	
	mov keep_ip, bx
	mov keep_cs, es
	push ds
	mov dx, offset SUBR_INT
	mov ax, seg SUBR_INT
	mov ds, ax
	
	mov ah, 25h			;устанавливаем вектор прерывания
	mov al, 08h
	int 21h
	
	pop ds
check_end:
	mov ah, 01h 			;получаем символ
	int 21h
	cmp al, 1bh			;программа работает, пока не будет нажат ESC
	je func_end
	jmp check_end
func_end:
	cli				;запрещаем прерывания от внешних устройств
	push ds
	mov dx, keep_ip
	mov ax, keep_cs
	mov ds, ax
	
	mov ah, 25h
	mov al, 08h
	int 21h
	
	pop ds
	sti				;разрешаем прерывания от внешних устройств
	ret
MAIN ENDP

CODE ENDS

END MAIN
