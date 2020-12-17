.686
.MODEL FLAT, C
.STACK
.DATA
.CODE
distribution PROC C arr_length:dword, arr:dword, lower_ranges_arr:dword, range_arr:dword

	mov ecx, 0			;������� ��� ������� �� �������
	mov ebx, [arr] 
	mov esi, [lower_ranges_arr] 
	mov edi, [range_arr] 

f1:
	mov edx, [ebx]		;����� ������� �������� �������
	push ebx			;��������� ��������� �� ������� �������
	sub ebx, ebx		;�������� ���������

f2:
	mov eax, ebx		;eax �������� ������� ������ ������� ������
	shl eax, 2			;������ �������� �� 4, ��� ��� ������ ������� �� 4 ����
	cmp edx, [esi+eax]	;���������� �������� ������� � ������� ����� ��������
	jle fe
	inc ebx
	jmp f2

fe:
	add eax, edi		;����� �������� ��������� �� ������� � �������������� ������� ��� �����������������
	mov edx, [eax]
	inc edx
	mov [eax], edx
	pop ebx				;�������� ������� ������� � ��������� �� �����
	add ebx, 4
	inc ecx				;�������������� ������ �������
	cmp ecx, arr_length
	jl f1

ret
distribution ENDP

END 