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

#include <km_alltypes.h>
#include <sys_call.h>
#include <km_io.h>
#include <alltypes_arch.h>

#include "mmap.h"
#include "sys_ret.h"

#define OFF_MASK ((-0x2000ULL << (8 * sizeof(syscall_arg_t) - 1)) | (4096ULL - 1))

void* km_mmap(void* start, size_t len, int prot, int flags, int fd, off_t off)
{
	long ret = 0;
	if(off & OFF_MASK)
		return MAP_FAILED;
	if(len >= PTRDIFF_MAX)
		return MAP_FAILED;

	ret = __syscall6(__sys_mmap, start, len, prot, flags, fd, off);

	if(ret == -KM_EPERM && !start && (flags & MAP_ANON) && !(flags & MAP_FIXED))
		ret = -KM_ENOMEM;
	return (void*)syscall_ret(ret);
}

static void dummy(void) {}
weak_alias(dummy, __vm_wait);

int km_unmap(void* start, size_t len)
{
    __vm_wait();
    return __syscall2(__sys_munmap, start, len);
}
