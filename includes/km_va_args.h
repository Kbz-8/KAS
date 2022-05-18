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

#ifndef __KM_VA_ARGS__
#define __KM_VA_ARGS__

typedef char* km_va_list;
#define km_va_start(ap, parmn) (void)((ap) = (char*)(&(parmn) + 1))
#define km_va_arg(ap, type) (((type*)((ap) = ((ap) + sizeof(type))))[-1])
#define km_va_end(ap) (void)((ap) = 0)

#endif // __KM_VA_ARGS__
