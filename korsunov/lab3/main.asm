AStack SEGMENT STACK
	DW 12 DUP(?)
AStack ENDS

DATA SEGMENT
a 	DW 3
b 	DW 5
i 	DW -5
k 	DW 5
i1 	DW ?
i2 	DW ?
res DW ?
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, SS:AStack, DS:DATA
	
Main PROC FAR
	mov ax, DATA
	mov ds, ax
	
f1_1:
	mov ax, a
	cmp ax, b
	jle f1_2
	mov ax, i
	sal ax, 1
	neg ax
	add ax, 15
	mov i1, ax
	jmp f2_1
	
f1_2:
	mov ax, i
	sal ax, 1
	add ax, i
	add ax, 4
	mov i1, ax
	jmp f2_2
	
f2_1:
	mov ax, i
	mov cl, 2
	sal ax, cl
	sub ax, 5
	neg ax
	mov i2, ax
	jmp f3_1
	
f2_2:
	mov ax, i
	sal ax, 1
	add ax, i
	neg ax
	add ax, 10
	mov i2, ax
	
f3_1:
	cmp k, 0
	jge f3_2
	mov ax, i1
	sub ax, i2
	cmp ax, 0
	jge f3_write
	neg ax
	jmp f3_write
	
f3_2:
	mov ax, i2
	cmp ax, 0
	jge f3_2_max
	neg ax
	
f3_2_max:
	cmp ax, 7
	jge f3_write
	mov ax, 7
	
f3_write:
	mov res, ax
	mov ah, 4ch
	int 21h
	
Main ENDP
CODE ENDS
	END Main