AStack SEGMENT STACK
    DW 256 DUP(?)   ; 1 килобайт
AStack ENDS


DATA SEGMENT

INT_IP DW 0     ; IP прерывания
INT_CS DW 0     ; CS прерывания
GREETINGS db "Hello, World!$"

DATA ENDS


CODE SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:AStack


my_interrupt PROC FAR

    push ax
    push dx

    mov ah, 09h
    mov dx, offset GREETINGS
    int 21h

    pop dx
    pop ax

    mov al, 20h
    out 20h, al
    iret

my_interrupt ENDP

Main PROC FAR
    mov ax, DATA
    mov ds, ax

    mov ah, 35h
    mov al, 1ch
    int 21h
    mov INT_IP, bx  ; сохраняем информацию о прерывании
    mov INT_CS, es

    push ds
    mov dx, offset my_interrupt ; суем в dx смещение процедуры в dx
    mov ax, seg my_interrupt    ; суем в ax сегмент процедуры
    mov ds, ax                  ; помещаем сегмент в ds
    mov ah, 25h                 ; функция установки вектора прерывания
    mov al, 1ch                 ; номер вектора
    int 21h                     ; запускаем изменение  прерывания
    pop ds

    int 1ch ; вызываем созданное прерывание

    cli
    push ds
    mov dx, INT_IP
    mov ax, INT_CS
    mov ds, ax
    mov ah, 25h
    mov al, 1ch     ; номер прерывания
    int 21h         ; восстанавливаем старый вектор
    pop ds
    sti

    mov ah, 4ch
    int 21h
    
Main ENDP


CODE ENDS
END Main