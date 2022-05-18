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

#ifndef __KM_MEMORY__
#define __KM_MEMORY__

#include "km_alltypes.h"

#define malloc(x) km_malloc(x) // replacing all malloc by km_malloc due to conflict between malloc and sbrk
#define realloc(x) km_realloc(x)
#define calloc(x, y) km_calloc(x, y)
#define free(x) km_free(x)

void* km_malloc(size_t size);
void* km_malloc_shared(size_t size);
int km_free(void* ptr);
void* km_realloc(void* ptr, size_t size);
void* km_calloc(size_t n, size_t size);

void* km_memmove(void* destination, const void* source, size_t num);
void* km_memset(void* ptr, int c, size_t size);
void* km_memcpy(void* dest, void* src, size_t size);

void km_init_gc(void);
void km_end_gc(void);

#endif // __KM_MEMORY__
