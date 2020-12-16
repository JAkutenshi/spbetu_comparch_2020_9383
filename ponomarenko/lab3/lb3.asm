AStack SEGMENT STACK
	DW 32 DUP(?)
AStack ENDS

DATA SEGMENT
a	DW	1	;i1 = -22 i2 = -24 res = 46
b	DW	2
i	DW	3
k	DW	4
i1	DW	?
i2	DW	?
res	DW	?
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA, SS:AStack

Main PROC FAR
	mov ax, DATA
	mov ds, ax

f1:
	mov ax, a
	cmp ax, b
	jle f1_2       ; если первое < или = второму
	mov ax, i	; ax = i
	shl ax, 1	; ax = 2i
	shl ax, 1	; ax = 4i
	neg ax		; ax = -4i
	add ax, 7 	; ax = 7-4i
	mov i1, ax	; i1 = 7-4i
	jmp f2_1
	;7-4i (a>b)
	;8-6i (a<=b)
	
f1_2:
	mov ax, i	; ax = i
	shl ax, 1	; ax = 2i !!!!!!!!!!!!!!!!!!
	mov bx, ax 	; bx = 2i
	shl ax, 1	; ax = 4i
	add ax, bx 	; ax = 6i
	neg ax		; ax = -6i
	add ax, 8	; ax = 8-6i
	mov i1, ax	; i1 = 8-6i
	
f2:
	sub ax, 2	; ax = 6-6i
	mov i2, ax	; i2 = 6-6i
	jmp f3
	;20-4i (a>b)
	;-(6i-6) (a<=b)
	
f2_1: ; a > b
	add ax, 13 	; ax = 20-4i
	mov i2, ax	; i2 = 20-4i
	jmp f3
	
f3:
	mov ax, k	; ax = k
	cmp ax, 0	; if ax = 0
	je f3_1
	mov ax, i1	; ax = i1
	cmp ax, i2	; if ax < i2
	jl f3_min1
	mov ax, i2	; ax = i2
	mov res, ax	; res = i2 
	jmp f_end
	;|i1 + i2| (k=0)
	;min(i1,i2) (k!= 0)	
	
f3_1:
	mov ax, i1	; ax = i1
	add ax, i2	; ax = i1+i2
	cmp ax, 0	; if ax < 0
	jl f3_abs
	mov res, ax	; res = i1+i2
	jmp f_end
	
f3_min1:
	mov ax, i1	; ax = i1
	mov res, ax	; res = i1
	jmp f_end
	
f3_abs:
	neg ax		; ax = -(i1+i2)
	mov res, ax 	; res = -(i1+i2)
	jmp f_end

f_end:
	mov ah, 4ch
	int 21h
	
Main	ENDP
CODE	ENDS
	END Main
