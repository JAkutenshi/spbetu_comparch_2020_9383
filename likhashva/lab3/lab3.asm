AStack SEGMENT STACK
        DW 32 DUP(?)
AStack ENDS

DATA SEGMENT
a	DW	1
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


f1_1:
	mov ax, a
	cmp ax, b
	jg f1_2		;if a>b
			;a<=b
	mov ax, i        
	shl ax, 1	;ax = 2*i
	mov bx, ax	;bx = 2*i
	shl ax, 1	;ax = 4*i
	add ax, bx	;ax = 6*i
	sub ax, 10	;ax = 6*i - 10
	mov i1, ax
	
	jmp f2_1
f1_2:
	mov ax, i
	shl ax, 1       ;ax = 2*i
	shl ax, 1       ;ax = 4*i
	add ax, 3       ;ax = 4*i+3
	neg ax	        ;ax = -ax
	mov i1, ax


f2_1:
	mov ax, a
	cmp ax, b
	jg f2_2		;if a>b
			;a<=b
	mov ax, i        
	shl ax, 1	;ax = 2*i
	mov bx, ax	;bx = 2*i
	shl ax, 1	;ax = 4*i
	add ax, bx	;ax = 6*i
	neg ax		;ax = -ax
        add ax, 4       ;ax = -6*i+4
	
	mov i2, ax
	jmp f3

f2_2:
	mov ax, i
	shl ax, 1	;ax = 2*i
    	add ax, i	;ax = 3*i
   	add ax, 6	;ax = 3*i + 6
   	mov i2, ax


f3:
	mov ax, k
	cmp k, 0
	jl f3_1		;if k < 0
	
	mov ax, i2
	cmp ax, 0	;if ax < 0
	jl f_abs	;then |ax|
	
	jmp f3_cmp_6

f3_1:
	mov ax, i1	;ax = i1

	cmp ax, 0	;if ax < 0
        jl f_abs_1	;then ax = |ax|
       
        mov res, ax
        mov ax, i2
       	cmp ax, 0	;if ax < 0
        jl f_abs_2	;then ax = |ax|

        add res, ax     ;res = |i1|+|i2|
	jmp f3_res
f_abs:
	neg ax		;ax = -ax
	jmp f3_cmp_6

f3_cmp_6:
	cmp ax, 6	;if ax < 6
	jl f3_6		;res = 6
	jmp f3_res

f3_res:
	mov res, ax	;else res = ax
	jmp f_end
	
f_abs_1:
	neg ax		;ax = |ax|
        mov res, ax
        mov ax, i2
       	cmp ax, 0	;if ax < 0
        jl f_abs_2	;then ax = |ax|

        add res, ax     ;res = |i1|+|i2|
	jmp f3_res

f_abs_2:
        neg ax          ;ax = |ax|
        add res, ax     ;res = |i1|+|i2|
	jmp f3_res

f3_6:
	mov res, 6	;res = 6
	jmp f_end	

f_end:
	mov ah, 4ch
	int 21h
	
Main	ENDP
CODE	ENDS
	END Main
