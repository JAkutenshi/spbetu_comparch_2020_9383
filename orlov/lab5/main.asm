AStack SEGMENT STACK
  DB 1024 DUP(?)

AStack ENDS

DATA SEGMENT
  KEEP_CS DW 0 ;хранение сегмента
  KEEP_IP DW 0 ;хранение смещения прерывания

DATA ENDS

CODE SEGMENT
  ASSUME CS:CODE, DS:DATA, SS:AStack


SUBR_INT PROC FAR
    push ax	;сохраняем все изменяемые регистры
    push dx

    ; подача звукового сигнала
    Sound:
	; Управление высотой звука динамика 
    MOV   AL, 10110110b     ; Канал 2, режим 2, оба байта
    OUT   43h, AL           ; Установка режима для 2-го канала 
    MOV   AX, 300           ; Выбор высоты звука 
    OUT   42h, AL           ; Включить таймер, который
                                ; будет выдавать импульсы на 
                                ; динамик с заданной частотой
    MOV   AL, AH 
    OUT   42h, AL           ; Занесение высоты звука в порт динамика 
    IN    AL, 61h           ; Получить состояние динамика
    MOV   AH, AL            ; И сохранить его в AH
    OR    AL, 00000011b     ; Установить два младших бита
    OUT   61h, AL           ; Включить динамик	


    ; выключаем звук
    Sound_OFF:
    loop Sound_OFF
    mov al, 61h
    out 61h, al

    pop dx            ; восстанавливаем регистры
    pop ax
    mov al, 20h ; разрешение обработки прерываний
    out 20h, al ; более низкого уровня

    iret        ; конец прерывания
  SUBR_INT ENDP

MAIN PROC FAR
  mov ax, DATA
  mov ds, ax

  mov ah, 35h           ; ф-ия получения вектора
  mov al, 1Ch           ; номер прерывания
  int 21h

  mov KEEP_IP, bx       ; запомнили смещение
  mov KEEP_CS, es       ; запомнили сегмент вектора прерывания

  push ds               ; сохранили ds

  mov ax, seg SUBR_INT     ; сегмент процедуры в ax
  mov dx, offset SUBR_INT  ; смещение процедуры
  mov ds, ax

  mov ah, 25h             ; функция установки вектора
  mov al, 1Ch             ; номер вектора
  int 21h                 ; изменение прерывания
  pop ds                  ; восстанавливаем ds


  int 1Ch                ; наше прерывания

	mov cx, 0Fh      ;задержка
    mov dx, 4240h    ;для корректного
    mov ah, 86h      ;вывода звукового
    int 15h          ;сигнала


  CLI
  push ds

  mov dx, KEEP_IP     ; восстановили смещение для прерывания
  mov ax, KEEP_CS     ; восстановили сегмент прерывания
  mov ds, ax

  mov ah, 25h         ; функция установки вектора
  mov al, 1Ch         ; номер нашего прерывания

  int 21h             ; изменили прерывания
  pop ds

  STI

  mov ah, 4ch
  int 21h

MAIN ENDP
CODE ENDS
END MAIN