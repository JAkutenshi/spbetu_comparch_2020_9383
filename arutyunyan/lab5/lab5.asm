AStack SEGMENT STACK
    dw 256 DUP(?)   ; 1 килобайт
AStack ENDS


DATA SEGMENT

INT_IP dw 0     ; IP прерывания
INT_CS dw 0     ; CS прерывания
GREETINGS db "This interrupt is working!", 10, 13, '$'

DATA ENDS


CODE SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:AStack


my_interrupt PROC FAR
    jmp int_start

    SAVED_SP dw 0
    SAVED_SS dw 0
    SAVED_AX dw 0
    INT_STACK dw 16 DUP(?)

int_start:
    mov SAVED_SP, sp
    mov SAVED_AX, ax
    mov ax, ss
    mov SAVED_SS, ax
    mov ax, SAVED_AX
    mov sp, offset int_start
    mov ax, seg INT_STACK
    mov ss, ax


    push ax
    push dx

    mov ah, 09h
    mov dx, offset GREETINGS
    int 21h

    pop dx
    pop ax


    mov SAVED_AX, ax
    mov sp, SAVED_SP
    mov ax, SAVED_SS
    mov ss, ax
    mov ax, SAVED_AX


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

    input:
        mov ah, 1
        int 21h
        cmp al, 71h
        jne input

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
