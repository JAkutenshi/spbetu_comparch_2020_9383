AStack SEGMENT STACK
  DB 1024 DUP(?)

AStack ENDS

DATA SEGMENT
  KEEP_CS DW 0 ;хранение сегмента
  KEEP_IP DW 0 ;хранение смещения прерывания

DATA ENDS

CODE SEGMENT
  ASSUME CS:CODE, DS:DATA, SS:AStack


SUBR_INT PROC FAR

	jmp procedure
	
	KEEP_SS DW 0
    KEEP_SP DW 0
    KEEP_AX DW 0
    MY_STACK DW 1024 DUP(?)
	
	procedure:
		MOV KEEP_SP, SP
		MOV KEEP_AX, AX
		MOV AX, SS
		MOV KEEP_SS, AX
		MOV AX, KEEP_AX
		MOV SP, OFFSET procedure
		MOV AX, seg MY_STACK
		MOV SS, AX
	
    push ax	;сохраняем все изменяемые регистры
    push dx

    ; подача звукового сигнала
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

    pop dx            ; восстанавливаем регистры
    pop ax
	
	MOV  KEEP_AX, AX
    MOV SP, KEEP_SP
    MOV AX, KEEP_SS
    MOV SS, AX
    MOV AX, KEEP_AX
	
    mov al, 20h ; разрешение обработки прерываний
    out 20h, al ; более низкого уровня

    iret        ; конец прерывания
  SUBR_INT ENDP

MAIN PROC FAR
  mov ax, DATA
  mov ds, ax

  mov ah, 35h           ; ф-ия получения вектора
  mov al, 1Ch           ; номер прерывания
  int 21h

  mov KEEP_IP, bx       ; запомнили смещение
  mov KEEP_CS, es       ; запомнили сегмент вектора прерывания

  push ds               ; сохранили ds

  mov ax, seg SUBR_INT     ; сегмент процедуры в ax
  mov dx, offset SUBR_INT  ; смещение процедуры
  mov ds, ax

  mov ah, 25h             ; функция установки вектора
  mov al, 1Ch             ; номер вектора
  int 21h                 ; изменение прерывания
  pop ds                  ; восстанавливаем ds


  BUTTON_LOOP:
    mov ah, 00h
    int 16h
    cmp al, 27
    je exit
    loop BUTTON_LOOP

  exit:
  CLI
  push ds

  mov dx, KEEP_IP     ; восстановили смещение для прерывания
  mov ax, KEEP_CS     ; восстановили сегмент прерывания
  mov ds, ax

  mov ah, 25h         ; функция установки вектора
  mov al, 1Ch         ; номер нашего прерывания

  int 21h             ; изменили прерывания
  pop ds

  STI

  mov ah, 4ch
  int 21h

MAIN ENDP
CODE ENDS
END MAIN 