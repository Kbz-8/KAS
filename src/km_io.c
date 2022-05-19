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

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include <kmlib.h>

size_t km_print(const char* out)
{
    size_t len = km_strlen(out);
	write(STDOUT_FILENO, out, len);
    return len;
}

size_t km_println(const char* out)
{
    size_t len = km_strlen(out);
	write(STDOUT_FILENO, out, len);
	write(STDOUT_FILENO, "\n", 1);
    return len + 1;
}

size_t km_printf(const char* out, ...)
{
	km_va_list args = NULL;
	km_va_start(args, out);

	char* buffer = km_vsprintf(out, args);

	km_va_end(args);

    size_t len = km_strlen(buffer);

	write(STDOUT_FILENO, buffer, len);

    return len;
}


km_file km_fopen(const char* path, int mode)
{
	__km_asm_internal_fopen();
}

void km_fwrite(km_file file, const char* message, int len)
{
	__km_asm_internal_fwrite(file, message, len);
}

void km_fread(km_file file, char* buffer)
{
	__km_asm_internal_fread(file, buffer);
}

void km_fclose(km_file file)
{
	__km_asm_internal_fclose(file);
}
