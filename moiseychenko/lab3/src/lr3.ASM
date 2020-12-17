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
	jg f2_1		;if a>b
	mov ax, i
	shl ax, 1	;ax = 2*ax
	mov bx, ax	;bx = 2*ax
	shl ax, 1	;ax = 4*ax
	add ax, bx	;ax = 6*ax
	sub ax, 10	;ax = ax - 10
	mov i1, ax
  jmp f6
f2_1:
	mov ax, i
	shl ax, 1
	shl ax, 1
	add ax, 3
	neg ax
	mov i1, ax
	jmp f6_1

f6:
  mov ax, i
  add ax, 1          ; ax = i + 1
  mov bx, ax         ; bx = i + 1
  shl ax, 1          ; ax = 2 * (i + 1)
  add ax, bx         ; ax = 3 * (i + 1)
  mov bx, 5
  sub bx, ax         ; bx = 5 - (1 + i) * 3
  mov i2, bx
  jmp f5
f6_1:
  mov ax, i
  add ax, 1          ; ax = i + 1
  shl ax, 1          ; ax = 2 * (i + 1)
  sub ax, 4          ; ax = ax - 4
  mov i2, ax
  jmp f5
f5:
  mov ax, k
  cmp ax, 0
  je f5_cmp_6         ;k = 0
  jmp f5_sum_1        ;k != 0

f5_cmp_6:               ;проверяем i1 на знак
  mov bx, i1
  cmp bx, 0
  jl f5_neg
  jmp f5_cmp_6_1

f5_neg:                 ;если i1 < 0, меняем знак по модулю
  neg bx
  jmp f5_cmp_6_1

f5_cmp_6_1:             ;основная функция сравнения
  mov cx, 6
  cmp bx, cx
  jl res_i1
  jmp res_6

f5_sum_1:               ;проверка на положительность i1
  mov bx, i1
  cmp bx, 0
  jl f5_neg_sum
  jmp f5_sum_2
f5_sum_2:
  mov cx, i2          ;проверка на положительность i2
  cmp cx, 0
  jl f5_neg_sum_2
  jmp f5_res_sum

f5_neg_sum:
  neg bx
  jmp f5_sum_2
                           ;две функции для смены знака
f5_neg_sum_2:
  neg cx
  jmp f5_res_sum

f5_res_sum:              ;сложение
  mov ax, bx
  add ax, cx
  mov res, ax
  jmp f_end


res_6:
  mov res, 6
  jmp f_end

                            ;запись результата функции при k = 0
res_i1:
  mov res, bx
  jmp f_end

f_end:
	mov ah, 4ch
	int 21h

Main	ENDP
CODE	ENDS
	END Main
