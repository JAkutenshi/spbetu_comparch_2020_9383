AStack  SEGMENT STACK
    DB 1024 DUP(?)
AStack  ENDS

DATA    SEGMENT
    KEEP_CS DW 0    ;для хранения сегмента
    KEEP_IP DW 0    ;и смещения вектора прерывания
    TEXT DB 'Hello world!$'
DATA    ENDS

CODE    SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:AStack
	
MY_INT PROC FAR
    jmp begin
    KEEP_SS DW 0
	KEEP_SP DW 0
	KEEP_AX DW 0
    INTSTACK DW 16 DUP(?)
	
BEGIN:

	MOV KEEP_SP, SP
    MOV KEEP_AX, AX
    MOV AX, SS
    MOV KEEP_SS, AX
    MOV AX, KEEP_AX
    MOV SP, OFFSET BEGIN
    MOV AX, SEG INTSTACK
    MOV SS, AX
		
    PUSH AX ;сохранение изменяемых регистров
	PUSH DX 

	MOV AH,9H  ;выводим текст 
	MOV DX, OFFSET TEXT
    INT 21H

	POP DX ;восстановление регистров
	POP AX 
	
	MOV  KEEP_AX, AX
    MOV SP, KEEP_SP
    MOV AX, KEEP_SS
    MOV SS, AX
    MOV AX, KEEP_AX
	
	MOV AL,20H
	OUT 20H,AL
	IRET ;выход из прерывания
MY_INT ENDP


MAIN PROC FAR
    MOV AX, DATA
    MOV DS, AX
    ;сохраняем вектор прерывания
    MOV AH, 35H ; функция получения вектора
	MOV AL, 08H ; номер вектора
	INT 21H
	MOV KEEP_IP, BX ; запоминание смещения
	MOV KEEP_CS, ES ; и сегмента вектора прерывания

    ;устанавливаем новый вектор прерывания
	PUSH DS
	MOV DX, OFFSET MY_INT ; смещение для процедуры в DX
	MOV AX, SEG MY_INT ; сегмент процедуры
	MOV DS, AX ; помещаем в DS
	MOV AH, 25H ; функция установки вектора
	MOV AL, 08H ; номер вектора
	INT 21H ; меняем прерывание
	POP DS
	
    INT 08H
	
MY_LOOP:
    MOV AH, 01H
    INT 21H

    CMP AL, 13
    JE NEW_INT

    CMP AL, 27
    JNE MY_LOOP

    JMP MY_END
	
NEW_INT:
    INT 08H
    JMP MY_LOOP
	
MY_END:
    ;восстанавливаем старый вектор прерывания
    CLI
	PUSH DS
	MOV DX, KEEP_IP
	MOV AX, KEEP_CS
	MOV DS, AX
	MOV AH, 25H
	MOV AL, 08H
	INT 21H ; восстанавливаем старый вектор прерывания
	POP DS
	STI
	
    MOV AH, 4CH
    INT 21H
MAIN ENDP

CODE ENDS

END MAIN