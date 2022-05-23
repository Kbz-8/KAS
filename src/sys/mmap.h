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

#ifndef __KM_SYS_MMAP__
#define __KM_SYS_MMAP__

#include <km_alltypes.h>

// Flags for mmap
#define MAP_PRIVATE 0x0001
#define MAP_SHARED 0x0002
#define MAP_ANONYMOUS 0x0004
#define MAP_ANON MAP_ANONYMOUS
#define MAP_FIXED 0x0008

#define MAP_FAILED ((void*)-1)

// Protections on memory mapping
#define PROT_READ  0x1
#define PROT_WRITE 0x2
#define PROT_NONE  0x8
#define PROT_EXEC  0x4

void* km_mmap(void* start, size_t len, int prot, int flags, int fd, off_t off);
int km_unmap(void* addr, size_t length);

#endif // __KM_SYS_MMAP__
