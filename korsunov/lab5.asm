AStack SEGMENT STACK
	db 1024 DUP(?)
AStack ENDS

DATA SEGMENT
	KEEP_CS DW 0 ; для хранения сегмента
	KEEP_IP DW 0 ; и смещения вектора прерывания
	message DB 'Hello, world!', 0AH, 0DH, '$'
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA, SS:AStack
	
	SUBR_INT PROC FAR
	PUSH AX
	PUSH DX
	
	MOV AH, 9h
	MOV DX, OFFSET message
	INT 21h
	
	POP AX            ; восстанавливаем регистры
    POP DX

    MOV AL, 20h ; разрешение обработки прерываний
    OUT 20h, AL ; более низкого уровня


    IRET        ; конец прерывания
	SUBR_INT ENDP
	
	MAIN PROC FAR
		PUSH DS
		SUB AX, AX
		PUSH AX
		MOV AX, DATA
		MOV DS, AX
		
		MOV AH, 35H ; функция получения вектора
		MOV AL, 60h ; номер вектора
		INT 21H
		MOV KEEP_IP, BX ; запоминание смещения
		MOV KEEP_CS, ES ; и сегмента вектора прерывания
		
		PUSH DS
		MOV DX, OFFSET SUBR_INT ; смещение для процедуры в DX
		MOV AX, SEG SUBR_INT ; сегмент процедуры
		MOV DS, AX ; помещаем в DS
		MOV AH, 25H ; функция установки вектора
		MOV AL, 60H ; номер вектора
		INT 21H ; меняем прерывание
		POP DS
		
		INT 60h
		
		CLI
		PUSH DS
		MOV DX, KEEP_IP
		MOV AX, KEEP_CS
		MOV DS, AX
		MOV AH, 25H
		MOV AL, 60h
		INT 21H ; восстанавливаем старый вектор прерывания
		POP DS
		STI
		
		RET
		
	MAIN ENDP
	CODE ENDS
	END MAIN

		