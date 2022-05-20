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

%define SYS_EXIT  1
%define SYS_OPEN  5
%define SYS_WRITE 4
%define SYS_READ  3
%define SYS_CLOSE 6
%define SYS_MMAP  90

__km_asm_internal_exit:
    mov edi, ebx ; passing code to sys call
    mov eax, SYS_EXIT ; system call number (sys_exit)
    int 0x80   ; call kernel

__km_asm_internal_fopen:
    mov edx, r10
    mov edi, ebx
    mov esi, ecx
    mov r10, edx
    mov eax, SYS_OPEN ; call system file opener
    int 0x80   ; call kernel

__km_asm_internal_fwrite:
    mov edi, ebx
    mov esi, ecx
    mov eax, SYS_WRITE ; call system file writer
    int 0x80   ; call kernel

__km_asm_internal_fread:
    mov edi, ebx
    mov esi, ecx
    mov eax, SYS_READ ; call system file reader
    int 0x80   ; call kernel

__km_asm_internal_fclose:
    mov edi, ebx
    mov eax, SYS_CLOSE ; call system file closer
    int 0x80   ; call kernel

__km_asm_internal_cout:
    mov rax, 4        ; sys_write 
    mov rbx, 1        ; File descriptor 1, stdout
    mov rcx, rci      ; Pass the message
    mov rdx, rsi      ; Length of message
    int 0x80

__km_asm_internal_mmap:
    mov 
    mov eax, SYS_MMAP ; call sys mmap
    int 0x80
