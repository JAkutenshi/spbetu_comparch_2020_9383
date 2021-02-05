EOF EQU '$'

AStack  SEGMENT STACK
    DB 1024 DUP(?)
AStack  ENDS

DATA    SEGMENT
    KEEP_CS DW 0    ; для хранения сегмента вектора прерывания
    KEEP_IP DW 0    ; и смещения вектора прерывания
DATA    ENDS

CODE    SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:AStack

SUBR_INT PROC FAR
	PUSH AX
	PUSH DX
	PUSH CX
	
    MOV CX, 0088H
    MOV DX, 00FFH ; 0088H и 00FFH - 8 сек 
    MOV AH, 86H ;delay func
    INT 15H ;
	
    MOV AL, 20H
    OUT 20H,AL
	
    POP AX
    POP CX
    POP DX
    IRET
SUBR_INT ENDP

MAIN PROC FAR
    PUSH DS ; сохранение адреса начала PSP в стеке для последующего восстановления по команде ret
    MOV AX, DATA ; загрузка сегментного регистра данных
    MOV DS, AX
    
    MOV AH, 35H ; функция получения вектора
    MOV AL, 1CH ; номер вектора
    INT 21H
    MOV KEEP_IP, BX ; запоминание смещения
    MOV KEEP_CS, ES ; и сегмента вектора прерывания
    
    PUSH DS
    MOV DX, OFFSET SUBR_INT ; смещение для процедуры в DX
    MOV AX, SEG SUBR_INT ; сегмент процедуры
    MOV DS, AX ; помещаем в DS
    MOV AH, 25H ; функция установки вектора
    MOV AL, 1CH ; номер вектора
    INT 21H ; меняем прерывание
    POP DS
    
    INT 1CH
    
    CLI
    PUSH DS
    MOV DX, KEEP_IP
    MOV AX, KEEP_CS
    MOV DS, AX
    MOV AH, 25H
    MOV AL, 1CH
    INT 21H ; восстанавливаем старый вектор прерывания
    POP DS
    STI
    
    RET
MAIN ENDP
CODE ENDS
END MAIN