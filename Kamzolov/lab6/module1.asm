.586p
.MODEL FLAT, C
.CODE
PUBLIC C MODULE1
MODULE1 PROC C RESARRAY:DWORD, ARRAY:DWORD, SIZEARR:DWORD, XMIN:DWORD
	PUSH ESI
	PUSH EDI;���������� ���������
	PUSH EBP

	MOV EDI, RESARRAY
	MOV ESI, ARRAY
	MOV EAX, XMIN
	MOV ECX, SIZEARR
for_loop:
	MOV EBX, [ESI]
	SUB EBX, EAX
	MOV EBP, [EDI+4*EBX]
	INC EBP
	MOV [EDI+4*EBX], EBP
	ADD ESI, 4
	LOOP for_loop

	POP EBP
	POP EDI
	POP ESI
	
ret
MODULE1 ENDP
END