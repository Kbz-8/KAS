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

#define OFF_MASK ((-0x2000ULL << (8 * sizeof(long) - 1)) | 0xfff)

static void dummy1(int x) {}
static void dummy0(void) {}
weak_alias(dummy1, __vm_lock);
weak_alias(dummy0, __vm_unlock);

void* km_mmap(void* start, size_t len, int prot, int flags, int fd, off_t off)
{ 
	long value = 0;
	if(off & OFF_MASK)
    {
        km_errno = KM_EINVAL;
        return MAP_FAILED;
    }
    if(len >= PTRDIFF_MAX) 
    {
        km_errno = KM_ENOMEM;
        return MAP_FAILED;
    }
    if(flags & MAP_FIXED)
        __vm_lock(-1);

#ifdef __sys_mmap2
    value = __syscall6(__sys_mmap2, start, len, prot, flags, fd, off >> 12);
#else
	value = __syscall6(__sys_mmap, start, len, prot, flags, fd, off);
#endif

	if(value == -KM_EPERM && !start && (flags & MAP_ANON) && !(flags & MAP_FIXED))
		value = -KM_ENOMEM;

    void* ret = (void*)syscall_ret(value);

    if(flags & MAP_FIXED)
        __vm_unlock();

	return ret;
}

int km_unmap(void* start, size_t len)
{
    __vm_lock(-1);
    int ret = __syscall2(__sys_munmap, start, len);
    __vm_unlock();
    return ret;
}
