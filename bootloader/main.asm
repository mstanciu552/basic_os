[org 0x7c00]

KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl

mov bp, 0x9000
mov sp, bp

mov si, MSG_REAL_MODE
call printf

call load_kernel

call switch_to_pm

jmp $

%include "printf.asm"
%include "readDisk.asm"
%include "gdt.asm"
%include "switch_to_pm.asm"
%include "print_string_pm.asm"
%include "clear_screen.asm"

[bits 16]

load_kernel:
  mov bx, KERNEL_OFFSET
  mov dh, 15 
  mov dl, [BOOT_DRIVE]
  call readDisk

  mov si, MSG_LOAD_KERNEL
  call printf

  ret

[bits 32]
BEGIN_PM:
  ; call clear_screen

  mov ebx, MSG_PROT_MODE
  call print_string_pm
  
  call KERNEL_OFFSET

  jmp $

DISK_ERR_MSG db "Error loading from hard disk    ", 0x0a, 0x0d, 0
MSG_REAL_MODE db "Started in 16-bit real mode    ", 0x0a, 0x0d, 0
MSG_PROT_MODE db "Succesfully switched to 32-bit protected mode    ", 0
MSG_LOAD_KERNEL db "Loaded Kernel into memory     ", 0x0a, 0x0d, 0
WHITE_SPACE db " ", 0

BOOT_DRIVE: db 0

times 510 - ($ - $$) db 0
dw 0xaa55
