AStack  SEGMENT STACK
    DB 1024 DUP(?)
AStack  ENDS

DATA    SEGMENT
    KEEP_CS DW 0    ;для хранения сегмента
    KEEP_IP DW 0    ;и смещения вектора прерывания
DATA    ENDS


CODE    SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:AStack


MY_INT PROC FAR
    jmp start
    KEEP_SS DW 0
    KEEP_SP DW 0
    KEEP_AX DW 0
    MAS DW 12 DUP(?)
start:
    MOV KEEP_SP, SP
    MOV KEEP_AX, AX
    MOV AX, SS
    MOV KEEP_SS, AX
    MOV AX, KEEP_AX
    MOV SP, OFFSET start
    MOV AX, seg MAS
    MOV SS, AX


    push AX
    push DX 
 ;------ Часть кода выводящая звук
    MOV AL , 10110110b
    OUT 43H, AL; Set mode for 2nd channel
    MOV AX , 1000; Pitch of sound
    OUT 42H, AL
    MOV AL , AH
    OUT 42H, AL; Set it to speaker port
    IN AL, 61H
    MOV AH, AL
    OR AL,3
    OUT 61H, AL
    SUB CX, CX
    KILL_TIME:
        LOOP KILL_TIME
        MOV AL, AH
        OUT 61H, AL
 ;---------------------------------------------
    pop DX 
    pop AX 

    MOV  KEEP_AX, AX
    MOV SP, KEEP_SP
    MOV AX, KEEP_SS
    MOV SS, AX
    MOV AX, KEEP_AX


    mov al,20h
    out 20h,al
    iret
MY_INT ENDP


MAIN PROC FAR
    MOV AX, DATA
    MOV DS, AX
    ;сохраняем вектор прерывания
    MOV AH, 35H ; функция получения вектора
	MOV AL, 23H ; номер вектора
	INT 21H
	MOV KEEP_IP, BX ; запоминание смещения
	MOV KEEP_CS, ES ; и сегмента вектора прерывания

    PUSH DS
    MOV DX, OFFSET MY_INT ; смещение для процедуры в DX
    MOV AX, SEG MY_INT ; сегмент процедуры
    MOV DS, AX; помещаем в DS
    MOV AH, 25H; функция установки вектора
    MOV AL, 23H; номер вектора
    INT 21H; меняем прерывание
    POP DS

enter_ctrl_c:
    mov ah,0
    int 16h
    cmp al,3
    jne enter_ctrl_c

    INT 23H

    CLI
    PUSH DS
    MOV DX, KEEP_IP
    MOV AX, KEEP_CS
    MOV DS, AX
    MOV AH, 25H
    MOV AL, 23H
    INT 21H
    ; восстанавливаем старый вектор прерывания
    POP DS
    STI

    MOV AH, 4CH
    INT 21H

MAIN ENDP

CODE ENDS

END MAIN