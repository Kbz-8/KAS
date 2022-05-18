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

#ifndef __KM_STRINGS__
#define __KM_STRINGS__

#include "km_va_args.h"

size_t km_strlen(const char* str);
void km_strcpy(char* dest, const char* src);
void km_stradd(char* dest, const char* src);
void km_strrev(char* arr, int start, int end);

char* km_vsprintf(const char* src, km_va_list args);

char* km_nitoa(int num, char* dest, int pos, int base);
char* km_itoa(int num, char* dest, int base);
char* km_nlltoa(long long num, char* dest, int pos, int base);
char* km_lltoa(long long num, char* dest, int base);
#define KM_MAX_PRECISION 10
char* km_nftoa(double num, char* dest, int pos, int precision);
char* km_ftoa(double num, char* dest, int precision);

#endif // __KM_STRINGS__
