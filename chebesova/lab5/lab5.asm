AStack  SEGMENT STACK
    DB 1024 DUP(?)
AStack  ENDS

DATA    SEGMENT
    KEEP_CS DW 0    ;��� �������� ��������
    KEEP_IP DW 0    ;� �������� ������� ����������
    TEXT DB 'Hello world!$'
DATA    ENDS

CODE    SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:AStack

MY_INT PROC FAR
    PUSH AX ;���������� ���������� ���������
	PUSH DX 

	MOV AH,9H  ;������� ����� 
	MOV DX, OFFSET TEXT
    INT 21H

	POP DX ;�������������� ���������
	POP AX 
	MOV AL,20H
	OUT 20H,AL
	IRET ;����� �� ����������
MY_INT ENDP


MAIN PROC FAR
    MOV AX, DATA
    MOV DS, AX
    ;��������� ������ ����������
    MOV AH, 35H ; ������� ��������� �������
	MOV AL, 08H ; ����� �������
	INT 21H
	MOV KEEP_IP, BX ; ����������� ��������
	MOV KEEP_CS, ES ; � �������� ������� ����������

    ;������������� ����� ������ ����������
	PUSH DS
	MOV DX, OFFSET MY_INT ; �������� ��� ��������� � DX
	MOV AX, SEG MY_INT ; ������� ���������
	MOV DS, AX ; �������� � DS
	MOV AH, 25H ; ������� ��������� �������
	MOV AL, 08H ; ����� �������
	INT 21H ; ������ ����������
	POP DS
	
    INT 08H

    ;��������������� ������ ������ ����������
    CLI
	PUSH DS
	MOV DX, KEEP_IP
	MOV AX, KEEP_CS
	MOV DS, AX
	MOV AH, 25H
	MOV AL, 08H
	INT 21H ; ��������������� ������ ������ ����������
	POP DS
	STI
	
    MOV AH, 4CH
    INT 21H
MAIN ENDP

CODE ENDS

END MAIN