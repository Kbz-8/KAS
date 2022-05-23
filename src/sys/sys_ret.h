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

#ifndef __KM_SYS_RET__
#define __KM_SYS_RET__

#include <km_errno.h>

long syscall_ret(unsigned long r)
{
    if(r > -4096UL)
    {
        km_errno = -r;
        return -1;
    }
    return r;
}

#endif // __KM_SYS_RET__ 
