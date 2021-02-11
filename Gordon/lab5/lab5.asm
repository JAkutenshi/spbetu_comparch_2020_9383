EOF EQU '$'

AStack  SEGMENT STACK
    DB 1024 DUP(?)
AStack  ENDS

DATA    SEGMENT
    KEEP_CS DW 0    ; для хранения сегмента вектора прерывания
    KEEP_IP DW 0    ; и смещения вектора прерывания
	string DB 'Lr5 ','$'
DATA    ENDS

CODE    SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:AStack

SUBR_INT PROC FAR
	PUSH AX
	PUSH DX
	PUSH CX
	
	mov AH,09h				;(3)
	mov DX,offset string	;(4)
	int 21h					;(5)
	mov CX,1		;(1)Число шагов в демо-цикле
cycle:	push CX			;(2)Сохраним этот счетчик в стеке
	;Организуем программную задержку
	mov CX,50		;(6)Счетчик внешнего цикла
outer:	push CX			;(7)Сохраним его в стеке
	mov CX,65535		;(8)Счетчик внутреннего цикла
inner:	loop inner		;(9)Повторим команду loop 65535 раз
	pop CX			;(10)Восстановим внешний счетчик
	loop outer		;(11)Повторим все это 100 раз
	pop CX			;(12)Восстановим счетчик демо-цикла
	loop cycle		;(13)Повторим демо-цикл CX=10 раз
	
    
	
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
    
	print:
	mov ah, 01h
	int 21h
	cmp al, 1bh ;esc
	jne print


	
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