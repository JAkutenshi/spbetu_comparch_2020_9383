AStack SEGMENT STACK
    DW 1024 DUP(?)   ; 1 килобайт
AStack ENDS


DATA SEGMENT
    KEEP_CS DW 0 ; для хранения сегмента
    KEEP_IP DW 0 ; и смещения вектора прерывания
    MSG     DB "This is my INT msg",10,13,'$'
DATA ENDS


CODE SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:AStack


SUBR_INT PROC FAR
    jmp ISTART
    KEEP_SP DW 0
    KEEP_SS DW 0
    KEEP_AX DW 0
    ISTACK  DW 16 DUP(?)
ISTART:
    MOV KEEP_SP, SP
    MOV KEEP_AX, AX
    MOV AX, SS
    MOV KEEP_SS, AX
    MOV AX, KEEP_AX
    MOV SP, OFFSET ISTART
    MOV AX, SEG ISTACK
    MOV SS, AX

    PUSH AX             ; сохранение изменяемых регистров
    PUSH DX
        ;<действия по обработке прерывания>
        MOV DX, OFFSET MSG
        MOV AH, 09H
        INT 21H
    POP DX
    POP AX

;     MOV KEEP_AX, AX
    
    MOV AL, 20H
    OUT 20H,AL
    
    MOV SP, KEEP_SP
    MOV AX, KEEP_SS
    MOV SS, AX
    MOV AX, KEEP_AX


    IRET
SUBR_INT ENDP


Main PROC FAR
    MOV AX, DATA
    MOV DS, AX

    MOV AH, 35H                 ; ф-ия получения вектора
    MOV AL, 1CH                 ; номер прерывания
    INT 21H
    MOV KEEP_IP, BX             ; запоминание смещения
    MOV KEEP_CS, ES             ; и сегмента вектора прерывания

    PUSH DS                     ; сохранение DS
    MOV DX, OFFSET SUBR_INT     ; смещение для процедуры в DX
    MOV AX, SEG SUBR_INT        ; сегмент процедуры через AX
    MOV DS, AX                  ; в DS
    MOV AH, 25H                 ; функция установки вектора
    MOV AL, 1CH                 ; номер вектора
    MOV AL, 60H                 ; номер вектора
    MOV AL, 23H                 ; номер вектора
    MOV AL, 08H                 ; номер вектора
    INT 21H                     ; меняем прерывание
    POP DS                      ; восстановление DS

    ; Далее может выполняться вызов нового обработчика прерывания.
label1:
    MOV AH, 01H
    INT 21H
    cmp AL, 21
    jne label1


    ; В конце программы восстанавливается старый вектор прерывания
    CLI
    PUSH DS
    MOV DX, KEEP_IP
    MOV AX, KEEP_CS
    MOV DS, AX
    MOV AH, 25H
    MOV AL, 1CH
    INT 21H                     ; восстанавливаем старый вектор прерывания
    POP DS
    STI

    MOV AH, 4CH
    INT 21H
Main ENDP
CODE ENDS
END Main
