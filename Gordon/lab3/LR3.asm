EOFLine  EQU  '$'         ; Определение символьной константы
a  EQU 2
B  EQU 1
I  EQU 3
K  EQU 0                         ;     "Конец строки"


; Стек  программы

AStack    SEGMENT  STACK
          DW 12 DUP(?)    ; Отводится 12 слов памяти
AStack    ENDS

; Данные программы
DATA      SEGMENT

;  Директивы описания данных

F1 DW 0
F2 DW 0
F3 DW 0
DATA      ENDS

; Код программы

CODE      SEGMENT
          ASSUME CS:CODE, DS:DATA, SS:AStack

; Головная процедура
Main      PROC  FAR
          push  DS       ;\  Сохранение адреса начала PSP в стеке
          sub   AX,AX    ; > для последующего восстановления по
          push  AX       ;/команде ret, завершающей процедуру  
          
          ;записываем условие для F1 
          
          MOV AX,a       ; Заносим значение а
          SUB AX,b       ; Вычитаем из а значение b
          cmp ax,0       ; Сравниваем полученное а с 0
          Jg Metka1      ; Переход к М1, если а>0
          MOV AX,I       ; Заносим значение i 
          SHL AX,1       ; Сдвиг на 1б (умножаем на 2)
		  ;MOV BX,I
          ADD AX,I       ; 2*i + i = 3i
          ;Mov BX,4       ; 
          ADD AX,4      ; Сложение (3*i + 4)
          MOV F1,AX      ; Присваиваем F1 значение Ах   
          CMP F1,AX    
          JE Fun2  
   Metka1:               ;   
          mov AX,I       ;
          SHL AX,1       ; 2*i
          MOV BX,15
          SUB BX,AX      ; 15 - 2*i
          MOV F1,BX      ; Присваиваем F1 значение Bх   
          
          

          ; записываем условие для F2 
          Fun2:
          JG Metka2      ; Переход к М1, если а>0
          mov AX,I       ; Заносим значение i 
          SHL AX,1       ; Сдвиг на 1б (умножаем на 2)
		  ;MOV BX,I
          ADD AX,I       ; 2*i + i = 3*i
          ;MOV BX,6
          ADD AX,6      ; 3*(i + 2) = 3*i + 6 
          MOV F2,Ax      ; Присваиваем F2 значение Ах 
          CMP F2,Ax      ; Сравнение результата
          JE  Fun3       ; Переход, если равно 
  Metka2:                ;
          MOV AX,I       ;
          SHL AX,1       ; 2*i
		  SHL AX,1       ; 2*i
		  ;MOV BX,I
          ADD AX,I       ; 5*i
		  ADD AX,I       ; 6*i
		  MOV BX,4
          SUB BX,AX      ; 4 - 6*i 
          MOV F2,BX      ; Присваиваем F2 значение Ах 
          
          ; записываем условие для F3 
           
          Fun3: 
          MOV AX,K       ;
          CMP AX,0       ;
          JNE Metka3     ; Если к/=0, то переход
          mov AX,F1      ;
          mov BX,F2      ; 
          ADD BX,AX      ; i1 + i2
          CMP BX,0       ; 
          JG Metka4      ;
						 ; i1 + i2 <= 0
          xor BX, 0FFFFh ; инверсия всех битов
		  inc BX         ; добавляем 1               
          mov F3,BX      ;
		  RET            ;
   Metka4:               ; i1 + i2 > 0
          mov F3,BX		 ; ответ записываем в F3
		  RET            ;
   Metka3:               ;
          MOV AX,F1      ;
          MOV BX,F2      ; 
          SUB BX,AX      ; 
          CMP BX,0       ;
		  JG Metka5      ;
          				 ; i2 <= i1
		  MOV F3,AX 
          ret 
Metka5:                  ;
          MOV BX,F2      ; i2 > i1
          MOV F3,BX      ;
          ret            ; Выход в DOS по команде,
                         ; находящейся в 1-ом слове PSP.
CODE      ENDS
Main      ENDP
          END main
