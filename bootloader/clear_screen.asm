[bits 32]

; VIDEO_MEMORY equ 0xb8000
; WHITE_ON_BLACK equ 0x0f

MAX_ROWS equ 25
MAX_COLS equ 80

clear_screen:
   pusha
   mov edx, VIDEO_MEMORY     

clear:
    mov al, 0 
    mov ah, WHITE_ON_BLACK

    cmp al, 4000
    je clear_done

    mov [edx], ax

    inc al
    add edx, 2

    jmp clear

clear_done:
    popa
    ret
