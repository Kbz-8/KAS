; This file is a part of the kmlib (kbz_8 main library)
;
; Copyright (C) 2022 @kbz_8
;
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program.  If not, see <https://www.gnu.org/licenses/>.

bits 64

global __km_asm_internal_exit
global __km_asm_internal_fopen
global __km_asm_internal_fwrite
global __km_asm_internal_fread
global __km_asm_internal_fclose
global __km_asm_internal_cout
global __km_asm_internal_mmap
global __km_asm_internal_munmap

%define SYS_EXIT  1
%define SYS_OPEN  5
%define SYS_WRITE 4
%define SYS_READ  3
%define SYS_CLOSE 6
%define SYS_MMAP  9
%define SYS_MUNMAP 0x0B

__km_asm_internal_exit:
    mov ebx, edi
    mov eax, SYS_EXIT ; system call number (sys_exit)
    int 0x80   ; call kernel

__km_asm_internal_fopen:
    mov ebx, edi
    mov esi, ecx
    mov edx, 0
    mov eax, SYS_OPEN ; call system file opener
    int 0x80   ; call kernel
    ret

__km_asm_internal_fwrite:
    mov ebx, edi
    mov esi, ecx
    mov eax, SYS_WRITE ; call system file writer
    int 0x80   ; call kernel

__km_asm_internal_fread:
    mov ebx, edi
    mov ecx, esi
    mov eax, SYS_READ ; call system file reader
    int 0x80   ; call kernel
    ret

__km_asm_internal_fclose:
    mov ebx, edi
    mov eax, SYS_CLOSE ; call system file closer
    int 0x80   ; call kernel

__km_asm_internal_cout:
    mov rax, 4        ; sys_write 
    mov rbx, 1        ; File descriptor 1, stdout
    mov rcx, rdi      ; Pass the message
    mov rdx, rsi      ; Length of message
    int 0x80

__km_asm_internal_mmap:
    mov rax, SYS_MMAP ; call sys mmap
    int 0x80
    ret

__km_asm_internal_munmap:
    mov rbx, rdi ; give pointer to mapped region
    mov rcx, rsi ; give length of mapped region
    mov rax, SYS_MUNMAP ; call munmap
    int 0x80 ; call kernel
    ret
