AStack SEGMENT STACK
    dw 256 DUP(?)   ; 1 килобайт
AStack ENDS


DATA SEGMENT

STRING_REPR db "00000000000000000000000000000000", 0ah, '$'  ; 32 символов для 32 бит
DXAX_STRING db "dx:ax = $"
ZERO_SYMBOL EQU '0'
ONE_SYMBOL EQU '1'
BITS_NUMBER EQU 32

DATA ENDS


CODE SEGMENT
    ASSUME cs:CODE, ds:DATA, ss:AStack


Main PROC FAR

    mov ax, DATA
    mov ds, ax
    
    mov dx, 07000h
    mov ax, 1
    call int_to_string

    mov ah, 09h
    mov dx, offset DXAX_STRING
    int 21h
    mov dx, offset STRING_REPR
    int 21h

    mov di, offset STRING_REPR
    call string_to_int
    
    ; теперь в dx:ax число из STRING_REPR
    call int_to_string
    mov ah, 09h
    mov dx, offset DXAX_STRING
    int 21h
    mov dx, offset STRING_REPR
    int 21h

    
    mov ah, 4ch
    int 21h
    
Main ENDP

int_to_string proc near

    push ax
    push dx
    push bx
    push cx
    push di

    ; если dx:ax >= 0, то доп.код совпадает с прямым
    mov bx, dx
    mov cl, 15
    shr bx, cl
    cmp bx, 1
    jne init_vars

    ; ===========
    ; в ax - часть доп.кода => отнимаем единицу до обратного кода
    sub ax, 1
    ; если произошелся заем в старший значащий бит, то cf = 1
    ; если cf = 1, то нужно отнять 1 еще и из dx
    jnc end_of_ready
    sub dx, 1

    end_of_ready:
        ; теперь инвертируем все биты кроме первого до прямого кода
        xor ax, 0ffffh
        xor dx, 07fffh
    ; ===========

    init_vars:
        mov di, offset STRING_REPR
        mov ch, 32 ; просто счетчик

    restart:
        mov cl, 16

    write_loop:
        dec ch
        dec cl

        cmp ch, 15
        jle mov_ax

        mov bx, dx
        jmp continue

    mov_ax:
        mov bx, ax

    continue:
        shr bx, cl
        and bx, 1
        cmp bx, 1
        je one_write

    zero_write:
        mov byte ptr [di], ZERO_SYMBOL
        jmp end_loop

    one_write:
        mov byte ptr [di], ONE_SYMBOL

    end_loop:
        inc di
        cmp ch, 16
        je restart
        cmp ch, 0
        jne write_loop
    

    pop di
    pop cx
    pop bx
    pop dx
    pop ax

    ret

int_to_string endp


; указатель на строку в di, возврат числа в ax
string_to_int proc near

    push di
    push cx
    push bx

    xor ax, ax
    xor dx, dx
    mov ch, BITS_NUMBER

    restart_2:
        mov cl, 16

    for_loop:
        dec ch
        dec cl

        mov bl, [di]
        cmp bl, ONE_SYMBOL
        jne loop_end

    one_read:
        mov bx, 1
        shl bx, cl

        cmp ch, 15
        jle to_ax

        add dx, bx
        jmp loop_end

    to_ax:
        add ax, bx

    loop_end:
        inc di
        cmp ch, 16
        je restart_2
        cmp ch, 0
        jne for_loop


    pop bx
    pop cx
    pop di

    ret

string_to_int endp


CODE ENDS
END Main