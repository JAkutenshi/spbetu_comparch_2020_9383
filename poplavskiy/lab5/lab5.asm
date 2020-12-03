Stk    SEGMENT  STACK
          DB 256 DUP(?)
Stk    ENDS 
DATA      SEGMENT
		KEEP_CS DW 0 ; для хранения сегмента
		KEEP_IP DW 0 ; и смещения прерывания
		Message2 db 'prerivanie',10,13,'$' ;строка для сообщения
DATA      ENDS
CODE      SEGMENT
          ASSUME CS:CODE, DS:DATA, SS:Stk
subr_int proc far ;начало процедуры
	push ax ;сохраняем все изменяемые регистры
	push dx ;сохраняем все изменяемые регистры

	mov ah,9h ;функция установки вектора
	mov dx,offset message2 ;в dx загружаем адрес сообщения Message2
	int 21h ;вывод строки на экран

	pop dx ;восстанавливаем регистры
	pop ax ;восстанавливаем регистры
	mov al,20h
	out 20h,al

	iret ;конец прерывания
subr_int endp ;конец процедуры

main proc far
	push ds
	sub ax,ax
	push ax
	mov ax,data
	mov ds,ax

	MOV  AH, 35H   ; функция получения вектора
	MOV  AL, 60H   ; номер вектора
	INT  21H
	MOV  KEEP_IP, BX  ; запоминание смещения
	MOV  KEEP_CS, ES  ; и сегмента

	push ds
	mov dx,offset subr_int

	mov ax,seg subr_int ;сегмент процедуры
	mov ds,ax ;помещаем в ds
	mov ah,25h ;функция установки вектора
	mov al,60h ;номер вектора
	int 21h ;меняем прерывание

	pop ds ;восстанавливаем ds 

	int 60h ;наше прерывание

	CLI
	PUSH DS
	MOV  DX, KEEP_IP
	MOV  AX, KEEP_CS
	MOV  DS, AX
	MOV  AH, 25H
	MOV  AL, 60H
	INT  21H          ; восстанавливаем вектор
	POP  DS
	STI
	ret
Main endp
code ends
	end Main
