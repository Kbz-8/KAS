bits 64
global __km_asm_interal_exit

__km_asm_interal_exit:
    mov eax, 1 ; system call number (sys_exit)
    int 0x80   ; call kernel
