AStack SEGMENT STACK
	DW 32 DUP(?)
AStack ENDS

DATA SEGMENT
a	DW	1
b	DW	4
i	DW	2
k	DW	0
i1	DW	?
i2	DW	?
res	DW	?
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA, SS:AStack

Main PROC FAR
	mov ax, DATA
	mov ds, ax

    mov ax, a
	cmp ax, b
	jle f1_b ;jump if a <= b

f1_a:   ;a > b
	mov ax, i
	shl ax, 1
    neg ax
	mov bx, ax
    add ax, 15
    mov i1, ax

	jmp f6

f1_b:  ;a <= b
	mov ax, i
	shl ax, 1
    add ax, i
	mov bx, ax
    add ax, 4
    mov i1, ax

    jmp f6


f6:
     mov ax, a         
     cmp ax, b          
     jle f6_b           ; a <= b
     mov ax, 1          ; кладем в ax 1
     add ax, i          ; ax = 1 + i
     shl ax, 1          ; домножим ax на 2
     sub ax, 4          ; ax = ax - 4
     mov i2, ax         
     jmp f5            

f6_b:
     mov ax, 1         
     add ax, i          ; ax = 1 + i
     mov bx, ax         ; кладем в bx i + 1
     shl ax, 1          ; домножим ax на 2
     add ax, bx         ; прибавим i + 1 и получим (i+1)*3
     mov bx, 5          ; кладем в bx 5
     sub bx, ax         ; bx - ax = 5 - (1 + i) * 3
     mov i2, bx         
     jmp f5
f5:
  	mov ax, k
  	cmp k, 0
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