AStack SEGMENT STACK
	DB 256 DUP(?)
AStack ENDS 


DATA SEGMENT
	KEEP_CS DW 0 ; для хранения сегмента
	KEEP_IP DW 0 ; и смещения вектора прерывания
	message DB 'This is user interruption$' ;строка для сообщения
DATA ENDS


CODE SEGMENT
	ASSUME CS:CODE, DS:DATA, SS:AStack



interrupt proc far  ;начало процедуры
	old_ax DW 0;
	old_dx DW 0;
	mov old_ax, ax
	mov old_dx, dx
	;push ax  ;сохраняем изменяемые регистры
	;push dx  ;сохраняем изменяемые регистры

	mov dx, offset message  ;в dx помещаем адрес message
	mov ah, 9h  ;функция установки вектора
	int 21h  ;вывод message

	;pop dx ;восстанавливаем регистры
	;pop ax ;восстанавливаем регистры

	mov al, 20h
	out 20h, al

	mov ax,  old_ax
	mov dx, old_dx

	iret  ;конец прерывания
interrupt endp  ;конец процедуры


main proc far
	push ds  ; сохранение адреса начала PSP в стеке для последующего восстановления по команде ret
	sub ax,ax ;
	push ax ;
	mov ax,data ; загрузка сегментного регистра данных
	mov ds,ax

	mov  ah, 35h   ;функция получения вектора
	mov  al, 60h   ;номер вектора
	int  21h   ; возвращение текущего значения вектора прерывания
	mov  KEEP_IP, bx  ;запоминание смещения
	mov  KEEP_CS, es  ;и сегмента вектора прерывания

	push ds
	mov dx, offset interrupt  ;смещение для процедуры в DX
	mov ax, seg interrupt ;сегмент процедуры
	mov ds, ax ;помещаем в ds
	mov ah, 25h ;функция установки вектора
	mov al, 60h ;номер вектора
	int 21h ;меняем прерывание

	pop ds ;восстанавливаем ds 

	int 60h ; вызов нового прерывание

	cli
	push ds
	mov dx, KEEP_IP
	mov ax, KEEP_CS
	mov ds, ax
	mov ah, 25h
	mov al, 60h
	int 21h   ;восстанавливаем старый вектор прерывания
	pop ds
	sti

	ret


MAIN ENDP
CODE ENDS
	END MAIN