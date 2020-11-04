dosseg
.model small
.stack 400h
.data
    KEEP_CS DW 0 	 ;для хранения сегмента
    KEEP_IP DW 0 	 ;для хранения смещения вектора прерывания
    message db 'Control + c$'
.code
    mov ax,@data
    mov ds,ax
    mov ah,35h   	 ;функция получения вектора
    mov al,23h   	 ;номер прерывания
    int 21h      	 ;получаем вектор 
    mov keep_cs,es 	 ;запоминание сегмента вектора прерывания
    mov keep_ip,bx 	 ;запоминание смещения 
    push ds	   	 ;сохраняем ds
    mov ax, seg MY_INT   ;сегмент процедуры помещаем в ax
    mov ds,ax	         ;перемещаем в ds
    mov dx,offset MY_INT ;смещение для процедуры помещаем в dx
    mov ah,25h		 ;функция установки вектора
    mov al,23h		 ;номер прерывания
    int 21h		 ;меняем прерывание
    pop ds
       jmp metka 
   
    MY_INT proc far
    push dx
    push ax
    mov dx,offset message	;смещение для сообщения 
    mov ah,9h			;номер функции
    int 21h			;вызов прерывания
    mov al,20h			;>разрешение обработки прерываний
    out 20h,al                  ;>более низкого уровня
    pop ax
    pop dx
    iret 
    MY_INT endp
metka:
   ; int 23h
    push ds			
    mov dx,keep_ip		;восстанавливаем смещение для прерывания
    mov ax,keep_cs		;восстанавливаем сегмент прерывания
    mov ds,ax			;заносим его в ds
    mov ah,25h			;функция установки вектора
    mov al,23h			;номер прерывания
    int 21h			;меняем прерывание
    pop ds			
    mov ah,4ch
    int 21h
end 
