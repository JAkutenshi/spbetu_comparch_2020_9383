EOF EQU '$'

AStack  SEGMENT STACK
    DB 1024 DUP(?)
AStack  ENDS

DATA    SEGMENT
    KEEP_CS DW 0    ;��� �࠭���� ᥣ���� ����� ���뢠���
    KEEP_IP DW 0    ;��� �࠭���� ᬥ饭�� ����� ���뢠���
DATA    ENDS

CODE    SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:AStack

MY_INT PROC FAR

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


    push AX
    push DX
 ;------ ����� ���� �뢮���� ���
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

    mov ax, DATA
    mov ds, ax
    GETVECTOR:      ;��࠭塞 ����� ���뢠���
    mov ah, 35h     ;�㭪�� ����祭�� �����
    mov al, 08h     ;����� �����
    int 21h
    mov KEEP_CS, es
    mov KEEP_IP, bx

    SETVECTOR:      ;��⠭�������� ���� ����� ���뢠���
    push ds
    mov dx, OFFSET MY_INT
    mov ax, SEG MY_INT
    mov ds, ax
    mov ah, 25h ;�㭪�� ��⠭���� �����
    mov al, 08h ;����� �����
    int 21h
    pop ds

    BUTTON_LOOP:
    mov ah, 00h
    int 16h
    cmp al, 27
    je RESTOREVECTOR
    loop BUTTON_LOOP

    RESTOREVECTOR:  ;����⠭�������� ���� ����� ���뢠���
    cli
    push ds
    mov dx, KEEP_IP
    mov ax, KEEP_CS
    mov ds, ax
    mov ah, 25h ;�㭪�� ��⠭���� �����
    mov al, 08h ;����� �����
    int 21h
    pop ds
    sti

    mov ah, 4ch ;�����襭�� �ணࠬ��
    int 21h

MAIN ENDP

CODE ENDS

END MAIN
