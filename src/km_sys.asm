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

%define SYS_EXIT   1
%define SYS_OPEN  5
%define SYS_WRITE 4
%define SYS_READ  3
%define SYS_CLOSE 6

__km_asm_internal_exit:
    mov rdi, ebx ; passing code to sys call
    mov eax, SYS_EXIT ; system call number (sys_exit)
    int 0x80   ; call kernel

__km_asm_internal_fopen:
    mov rdi, ebx
    mov rsi, ecx
    mov rdx, edx
    mov eax, SYS_OPEN ; call system file opener
    int 0x80   ; call kernel

__km_asm_internal_fwrite:
    mov rdi, ebx
    mov rsi, ecx
    mov rdx, edx
    mov eax, SYS_WRITE ; call system file writer
    int 0x80   ; call kernel

__km_asm_internal_fread:
    mov rdi, ebx
    mov rsi, ecx
    mov rdx, edx
    mov eax, SYS_READ ; call system file reader
    int 0x80   ; call kernel

__km_asm_internal_fclose:
    mov rdi, ebx
    mov eax, SYS_CLOSE ; call system file closer
    int 0x80   ; call kernel
