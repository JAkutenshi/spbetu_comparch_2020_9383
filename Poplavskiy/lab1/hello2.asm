; HELLO2 - “ç¥¡­ ï ¯à®£à ¬¬  N2  « ¡.à ¡.#1 ¯® ¤¨áæ¨¯«¨­¥ "€àå¨â¥ªâãà  ª®¬¯ìîâ¥à "
;          à®£à ¬¬  ¨á¯®«ì§ã¥â ¯à®æ¥¤ãàã ¤«ï ¯¥ç â¨ áâà®ª¨
;
;      ’…Š‘’  Žƒ€ŒŒ›

EOFLine  EQU  '$'         ; Ž¯à¥¤¥«¥­¨¥ á¨¬¢®«ì­®© ª®­áâ ­âë
                          ;     "Š®­¥æ áâà®ª¨"

; ‘â¥ª  ¯à®£à ¬¬ë

AStack    SEGMENT  STACK
          DW 12 DUP(?)    ; Žâ¢®¤¨âáï 12 á«®¢ ¯ ¬ïâ¨
AStack    ENDS

; „ ­­ë¥ ¯à®£à ¬¬ë

DATA      SEGMENT

;  „¨à¥ªâ¨¢ë ®¯¨á ­¨ï ¤ ­­ëå

HELLO     DB 'Hello Worlds!', 0AH, 0DH,EOFLine
GREETING  DB 'Student from 4350 - $'
DATA      ENDS

; Š®¤ ¯à®£à ¬¬ë

CODE      SEGMENT
          ASSUME CS:Code ;DS:DATA SS:AStack
; à®æ¥¤ãà  ¯¥ç â¨ áâà®ª¨
WriteMsg  PROC  NEAR
          mov   AH,9
          int   21h  ; ‚ë§®¢ äã­ªæ¨¨ DOS ¯® ¯à¥àë¢ ­¨î
          ret
WriteMsg  ENDP

; ƒ®«®¢­ ï ¯à®æ¥¤ãà 
Main      PROC  FAR
          push  DS       ;\  ‘®åà ­¥­¨¥  ¤à¥á  ­ ç «  PSP ¢ áâ¥ª¥
          sub   AX,AX    ; > ¤«ï ¯®á«¥¤ãîé¥£® ¢®ááâ ­®¢«¥­¨ï ¯®
          push  AX       ;/  ª®¬ ­¤¥ ret, § ¢¥àè îé¥© ¯à®æ¥¤ãàã.
          mov   AX,DATA             ; ‡ £àã§ª  á¥£¬¥­â­®£®
          mov   DS,AX               ; à¥£¨áâà  ¤ ­­ëå.
          mov   DX, OFFSET HELLO    ; ‚ë¢®¤ ­  íªà ­ ¯¥à¢®©
          call  WriteMsg            ; áâà®ª¨ ¯à¨¢¥âáâ¢¨ï.
          mov   DX, OFFSET GREETING ; ‚ë¢®¤ ­  íªà ­ ¢â®à®©
          call  WriteMsg            ; áâà®ª¨ ¯à¨¢¥âáâ¢¨ï.
          ret                       ; ‚ëå®¤ ¢ DOS ¯® ª®¬ ­¤¥,
                                    ; ­ å®¤ïé¥©áï ¢ 1-®¬ á«®¢¥ PSP.
Main      ENDP
CODE      ENDS
          END Main