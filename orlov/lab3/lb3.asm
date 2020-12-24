;       / 7 - 4*i , при a>b      (f1)
; f1 = <
;       \ 8 - 6*i , при a<=b	 (f2)
;
;       / -(6*i - 4) , при a>b	 (f11)
; f2 = <
;       \ 3*(i+2) , при a<=b	 (f22)
;
;       / max(i1,10-i2), при k<0 (f3)
; f3 = <
;       \ |i1 - i2| , при k>=0	 (absi)



AStack  SEGMENT STACK
    DW  32  DUP(?)
AStack  ENDS

DATA    SEGMENT
    A   DW  -2
    B   DW  1
    I   DW  4
    K   DW  0
    I1  DW  ?
    I2  DW  ?
    RES DW  ?
DATA    ENDS

CODE    SEGMENT
    ASSUME  CS:CODE, DS:DATA, SS:AStack

Main    PROC FAR
    mov ax, DATA
    mov ds, ax

f1  :
    mov ax, A
    cmp ax, B   ; сравнивает A и B
	jle f11
    mov ax, 1	; ax = 1
	sub ax, I	; ax = 1 - i
	shl ax, 1	; ax = 2 - 2i
	shl ax, 1	; ax = 4 - 4i
	add ax, 3	; ax = 7 - 4i
	mov I1,ax
	jmp f2

f2  :           ; A > B, так как мы переходим от f1
    add ax, I	; ax = 7 - 4i + i = 7 - 3i
	sub ax, 5	; ax = 7 - 3i - 5 = 2 - 3i	
	shl ax, 1	; ax = 2*(2 - 3i) = 4 - 6i = -(6i - 4)
	jmp f3


f11 :
	mov ax, 1	; ax = 1
	sub ax, I	; ax = 1 - i
    shl ax, 1	;ax = 2*(1 - i) = 2 - 2i
	shl ax, 1	;ax = 2*(2 - 2i) = 4 - 4i
	add ax, I	;ax = 4 - 3i
	shl ax, 1	;ax = 8 - 6i
	mov I1, ax
    jmp f22


f22 :
	neg ax	    ;ax = -(8 - 6i) = 6i - 8
	shr ax, 1	;ax = (6i - 8) / 2 = 3i - 4
	add ax, 10  ; ax = 3i - 4 + 10 = 3i + 6 = 3*(i + 2)
    jmp f3


f3  :
    cmp bx, K	;max(i1, 10 - i2)
    jle absi	
	neg ax		; ax = -i2
	add ax, 10  ; ax = 10 - i2
	cmp I1, ax  ; i1 <= 10 - i2 -> ax --- max
	jle fin
	mov ax, I1
	jmp fin

absi :
    neg ax 		;ax = -i2
	add ax, I1	;ax = i1 - i2
	cmp bx, ax	; i1 - i2 < 0 -> ax = -ax
	jle fin
	neg ax		;ax = -ax
	jmp fin

fin :
    mov RES, ax
    mov  ah, 4ch
    int  21h

Main    ENDP
CODE    ENDS
END Main 