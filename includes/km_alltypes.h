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

#ifndef __KM_ALLTYPES__
#define __KM_ALLTYPES__

#ifndef NULL
    #if __cplusplus >= 201103L
        #define NULL nullptr
    #elif defined(__cplusplus)
        #define NULL 0L
    #elif __STDC_VERSION__ >= 199901L
        #define NULL 0
    #else
        #define NULL ((void*)0)
    #endif
#endif

#ifndef CHAR_BIT
    #define CHAR_BIT 8
#endif

#define KM_MAX_PRECISION 10

typedef unsigned long size_t;
typedef long int off_t;

#ifndef __cplusplus
    typedef enum __attribute__((__packed__)) { false = 0, true = 1 } bool;
#endif

typedef unsigned int km_file;

#define KM_F_RONLY  00
#define KM_F_WONLY  01
#define KM_F_APPEND 02000
#define KM_F_CREATE 0100
#define KM_F_RW     02
#define KM_F_SYNC   04010000
#define KM_F_ASYNC  020000

#define weak_alias(name, aliasname) _weak_alias (name, aliasname)
#define _weak_alias(name, aliasname) extern __typeof (name) aliasname __attribute__ ((weak, alias (#name)));

#endif // __KM_ALL_TYPES__
