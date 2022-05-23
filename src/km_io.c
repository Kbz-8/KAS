/**
 * This file is a part of the kmlib (kbz_8 main library)
 *
 * Copyright (C) 2022 @kbz_8
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <kmlib.h>
#include <sys_call.h>

void __km_cout(const char* msg, size_t len)
{
    __syscall3(__sys_write, 1, msg, len);
}

size_t km_print(const char* out)
{
    size_t len = km_strlen(out);
	__km_cout(out, len);
    return len;
}

size_t km_println(const char* out)
{
    size_t len = km_strlen(out);
	__km_cout(out, len);
	__km_cout("\n", 1);
    return len + 1;
}

size_t km_printf(const char* out, ...)
{
	km_va_list args = NULL;
	km_va_start(args, out);

	char* buffer = km_vsprintf(out, args);

	km_va_end(args);

    size_t len = km_strlen(buffer);

	__km_cout(buffer, len);

    return len;
}

km_file km_fopen(const char* path, int mode)
{
	return __syscall2(__sys_open, path, mode);
}

void km_fwrite(km_file file, const char* message, int len)
{
	__syscall3(__sys_write, file, message, len);
}

void km_fread(km_file file, char* buffer)
{
	__syscall2(__sys_read, file, buffer);
}

void km_fclose(km_file file)
{
    __syscall1(__sys_close, file);
}
