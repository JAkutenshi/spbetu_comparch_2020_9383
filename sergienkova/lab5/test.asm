AStack  SEGMENT STACK
     DB 1024 DUP(?)
 AStack  ENDS

 DATA    SEGMENT
     KEEP_CS DW 0    ;для хранения сегмента
     KEEP_IP DW 0    ;и смещения вектора прерывания
     message DB 'CtrlC$'

 DATA    ENDS


 CODE    SEGMENT
     ASSUME CS:CODE, DS:DATA, SS:AStack


  MY_MESS PROC FAR
    push ax
    push dx

    mov ah, 9h               ; ф-ия установки веткора
    mov dx, offset message   ; в dx засунули адрес сообщения
    int 21h

    pop dx
    pop ax

    mov al, 20h        ; обработка прерывания более низкого уровня
    out 20h, al

    iret               ; конец нашего прерывания
 MY_MESS ENDP


 MAIN PROC FAR
    mov ax, DATA
    mov ds, ax

    mov ah, 35h      ; функция получения вектора прерываний
    mov al, 23h      ; номер прерывания
    int 21h          ;получаем вектор


    mov KEEP_IP, bx  ; запомнили смещение
    mov KEEP_CS, es  ; запомнили смещение сегмента вектора прерывания
    push ds

    mov dx, offset MY_MESS  ; смещение процедуры в dx
    mov ax, seg MY_MESS    ; сегмент процедуры занесли в ах
    mov ds, ax

    mov ah, 25h            ; устанавливаем вектор прерывания
    mov al, 23h            ; наше прерывание
    int 21h                ; поменяли прерывание на наше
    pop ds

 ctrl_c:
     mov ah,0
     int 16h
     cmp al,3
     jne ctrl_c

     INT 23H

     cli
     push ds
     mov dx, KEEP_IP        ; восстанавливаем смещение
     mov ax, KEEP_CS        ; восстанавливаем сегмент прерывания
     mov ds, ax
     mov ah, 25h            ; устанавливаем вектор
     mov al, 23h
     int 21h                ; меняем

     pop ds                  ; восстановили старое прерывание
     sti

     mov ah, 4ch
     int 21h

 MAIN ENDP
 CODE ENDS
 END MAIN
