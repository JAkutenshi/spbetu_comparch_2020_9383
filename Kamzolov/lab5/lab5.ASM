DATA SEGMENT
        KEEP_CS DW 0 ; для хранения сегмента
        KEEP_IP DW 0 ; и смещения вектора прерывания

        HELLO   DB 'Hello Worlds!  $',10,13,'$'
DATA ENDS


AStack    SEGMENT  STACK
          DW 12 DUP(?)    ; �⢮����� 12 ᫮� ������
AStack    ENDS



CODE      SEGMENT
          ASSUME CS:Code, DS:DATA, SS:AStack

SUBR_INT PROC FAR
        jmp start_proc
        KEEP_SS DW 0
	KEEP_SP DW 0
	KEEP_AX DW 0
        BStack DW 12 DUP(?)
start_proc:

        MOV KEEP_SP, SP
        MOV KEEP_AX, AX
        MOV AX, SS
        MOV KEEP_SS, AX

        MOV AX, KEEP_AX

        MOV SP, OFFSET start_proc


        MOV AX, seg BStack
        MOV SS, AX

        PUSH AX ; сохранение изменяемых регистров
        PUSH DX;

        MOV   DX, OFFSET HELLO
        MOV   AH,9
        int   21h  ; Вызов функции DOS по прерыванию

        POP DX;
        POP AX ; восстановление регистров

        MOV  KEEP_AX, AX
        MOV SP, KEEP_SP
        MOV AX, KEEP_SS
        MOV SS, AX
        MOV AX, KEEP_AX

        MOV AL, 20H
        OUT 20H,AL
        IRET
SUBR_INT ENDP


Main      PROC  FAR

        push  DS       ;\  Сохранение адреса начала PSP в стеке
        sub   AX,AX    ; > для последующего восстановления по
        push  AX       ;/  команде ret, завершающей процедуру.
        mov   AX,DATA             ; Загрузка сегментного
        mov   DS,AX               ; регистра данных.

        MOV AH, 35H ; функция получения вектора
        MOV AL, 60H ; номер вектора
        INT 21H ; возвращает текущее значение вектора прерывания
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

        int 60H; вызов измененного прерывания
for_loop:
        mov AH, 01H
        int 21H

        cmp AL, 13
        je prer

        cmp AL, 27
        jne for_loop

        jmp end_l
prer:
        int 60H
        jmp for_loop

end_l:
        CLI
        PUSH DS
        MOV DX, KEEP_IP
        MOV AX, KEEP_CS
        MOV DS, AX
        MOV AH, 25H
        MOV AL, 60H
        INT 21H ; восстанавливаем старый вектор прерывания
        POP DS
        STI

        RET
Main      ENDP
CODE      ENDS
          END Main
