.Model flat,c

.data
tempI dw 0	;��� ��������� ������� randArray
.code
funcMasm proc C 
	mov  eax,[esp+4] ; result � eax
	mov  ebx,[esp+8] ; LGrInt � ebx	
	mov  edx,[esp+12]; randArray � edx
	mov  di, [esp+16] ; NInt � di
	mov  cx, [esp+20] ; NumRanDat � cx
	and ecx,0000ffffh
	and edi,0000ffffh

	metka1:
		push ax	
		mov ax,[edx]
		mov tempI,ax	;� tempI - ������� ����� �� randArray
		pop ax

		mov esi,0		; ������ ��� �������� LGrInt � result
		push ecx		; ��������� ������� ��� �������� �����
		mov ecx,edi		; � ecx - ������� ��� ����������� �����
		metka2:
			push ebx	
			mov bx,[ebx+esi] ;� bx - ������� ������� �� LGrInt
			cmp tempI,bx	 ;���������� ��������� ����� ������� � ��������� ��������� ������
			jge metka3		 ;���� ����� ������ �������, �� ��� ������ � ��������
			add esi,2	 ;���������� � ������� ������� LGrInt 2
			pop ebx		
		loop metka2			 ;������������ ������ �� ����������� �����
		metka3:				 
			mov bx, [eax+esi] ;�������� ������� �� result
			inc bx			  ;����������� ��� �� 1 
			mov [eax+esi],bx  ;�������� ������� � result
			pop ebx	 
			pop ecx			  ;� ecx ������� ��� �������� �����
			add edx,2			 ;���������� � �������� ������� randArray 2
	loop metka1 
	
	ret
funcMasm endp
end