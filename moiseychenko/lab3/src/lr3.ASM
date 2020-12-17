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

f2:
	mov ax, a
	cmp ax, b
	jg f2_1           ; a > b
	mov ax, i
	shl ax, 1	        ; ax = 2*i
	mov bx, ax	      ; bx = 2*i
	shl ax, 1	        ; ax = 4*i
	add ax, bx	      ; ax = 6*i
	sub ax, 10	      ; ax = 6*i - 10
	mov i1, ax
	
	neg ax             ; ax = -6*i + 10
	shr ax, 1          ; ax = -3*i + 5
	sub ax, 3          ; ax = 5 -3*(i + 1)
	mov i2, ax
	jmp f5

f2_1:
	mov ax, i
	shl ax, 1          ; ax = 2*i
	shl ax, 1          ; ax = 4*i
	add ax, 3          ; ax = 4*i + 3
	neg ax             ; ax = -(4*i + 3)
	mov i1, ax

	neg ax             ; ax = 4*i + 3
	sub ax, 7          ; ax = 4*i - 4
	shr ax, 1          ; ax = 2*(i + 1) - 4
	mov i2, ax
	jmp f5

f5:
	mov bx, i1
	cmp bx, 0
	jl f5_neg
	jmp f5_1

f5_neg:
	neg bx
	jmp f5_1

f5_1:
	mov ax, k
	cmp ax, 0
	je f5_cmp_6        ;k = 0
	jmp f5_sum         ;k != 0

f5_cmp_6:
	cmp bx, 6
	jl res_i1
	jmp res_6

res_i1:
	mov res, bx
	jmp f_end

res_6:
	mov res, 6
	jmp f_end

f5_sum:
	mov cx, i2
	cmp cx, 0
	jl f5_neg_sum
	jmp f5_res_sum

f5_neg_sum:
	neg cx
	jmp f5_res_sum

f5_res_sum:
	mov ax, bx
	add ax, cx
	mov res, ax
	jmp f_end

f_end:
	mov ah, 4ch
	int 21h

Main	ENDP
CODE	ENDS
	END Main
