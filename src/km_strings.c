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

size_t km_strlen(const char* str)
{
	if(str == NULL)
		return 0;

	char c = *str;
	size_t size = 0;
	while(c != '\0')
	{
		c = *str++;
		size++;
	}
	return size;
}

void km_strcpy(char* dest, const char* src)
{
	km_memcpy(dest, src, km_strlen(src) - 1);
}

void km_stradd(char* dest, const char* src)
{
	km_memcpy(dest + km_strlen(dest) - 1, src, km_strlen(src) - 1);
}

void km_strrev(char* arr, int start, int end)
{
	// Fast string inversion

	if(start >= end)
		return;
	if(*(arr + end) == '\0')
		end--;

	// Fast variable inversion with XOR operation
	*(arr + start) = *(arr + start) ^ *(arr + end);
	*(arr + end)   = *(arr + start) ^ *(arr + end);
	*(arr + start) = *(arr + start) ^ *(arr + end);
	
	km_strrev(arr, start + 1, end - 1);
}

char* km_nitoa(int num, char* dest, int pos, int base)
{
	int i = pos;
	int r = 0;
	bool negative = false;

	if(num == 0)
	{
		dest[i] = '0';
		dest[i + 1] = '\0';
		return dest;
	}
	if(num < 0 && base == 10)
	{
		num *= -1;
		negative = true;
	}

	if(negative == true)
	{
		dest[i] = '-';
		i++;
	}

	while(num != 0)
	{
		r = num % base;
		dest[i] = (r > 9) ? (r - 10) + 'a' : r + '0';
		i++;
		num /= base;
	}
	km_strrev(dest, pos, i - 1);

	return dest;
}

char* km_itoa(int num, char* dest, int base)
{
	return km_nitoa(num, dest, 0, base);
}

char* km_nlltoa(long long num, char* dest, int pos, int base)
{
	int i = pos;
	int r = 0;
	bool negative = false;

	if(num == 0)
	{
		dest[i] = '0';
		dest[i + 1] = '\0';
		return dest;
	}
	if(num < 0 && base == 10)
	{
		num *= -1;
		negative = true;
	}

	if(negative == true)
	{
		dest[i] = '-';
		i++;
	}

	while(num != 0)
	{
		r = num % base;
		dest[i] = (r > 9) ? (r - 10) + 'a' : r + '0';
		i++;
		num /= base;
	}
	km_strrev(dest, pos, i - 1);

	return dest;
}

char* km_lltoa(long long num, char* dest, int base)
{
	return km_nlltoa(num, dest, 0, base);
}

static const double rounders[KM_MAX_PRECISION + 1] = {
	0.5,
	0.05,
	0.005,
	0.0005,
	0.00005,
	0.000005,
	0.0000005,
	0.00000005,
	0.000000005,
	0.0000000005,
	0.00000000005,
};

char* km_nftoa(double num, char* dest, int pos, int precision)
{
	int start_pos = 0;
	char c = 0;
	long int_part = 0;
	size_t length = pos;

	if(precision > KM_MAX_PRECISION)
		precision = KM_MAX_PRECISION;

	if(num < 0)
	{
		num = -num;
		dest[length] = '-';
		length++;
	}

	if(precision < 0)
	{
		if(num < 1.0) precision = 6;
		else if(num < 10.0) precision = 5;
		else if(num < 100.0) precision = 4;
		else if(num < 1000.0) precision = 3;
		else if(num < 10000.0) precision = 2;
		else if(num < 100000.0) precision = 1;
		else precision = 0;
	}

	if(precision)
		num += rounders[precision];

	int_part = (long)num;
	num -= int_part;

	if(!int_part)
	{
		dest[length] = '0';
		length++;
	}
	else
	{
		start_pos = length;
		while(int_part)
		{
			dest[length] = '0' + int_part % 10;
			length++;
			int_part /= 10;
		}
		km_strrev(dest, start_pos, length);
	}

	if(precision)
	{
		dest[length] = '.';
		length++;

		while(precision--)
		{
			num *= 10;
			c = num;
			dest[length] = '0' + c;
			length++;
			num -= c;
		}
	}

	return dest;
}

char* km_ftoa(double num, char* dest, int precision)
{
	km_nftoa(num, dest, 0, precision);
}

char* km_vsprintf(const char* src, km_va_list args)
{
	char c = 0;
	size_t max_length = km_strlen(src) + 256;
	char* buffer = (char*)km_malloc(sizeof(char) * max_length);
	size_t length = 0;

	while(c = *src++)
	{
		if(length > max_length)
		{
			max_length += 256;
			buffer = (char*)km_realloc(buffer, max_length);
		}

		if(c == '%')
		{
			switch(c = *src++)
			{
				case '%' : buffer[length] = '%'; length++; break;
				case 'c' : buffer[length] = km_va_arg(args, char); length++; break;

				case 's' : 
				{
					char* s_case = km_va_arg(args, char*);
					km_stradd(buffer, s_case);
					length += km_strlen(s_case) - 1;
					s_case = NULL;
					break;
				}
				
				case 'l':
				{
					c = *src++;
					if(c != 'd' && c != 'i')
					{
						c = *src++;
						if(c != 'd' && c != 'i')
							break;
					}
					long long ll_case = km_va_arg(args, long long);
					km_nlltoa(ll_case, buffer, length, 10);
					length += km_strlen(buffer + length) - 1;
					break;
				}

				case 'h':
				{
					c = *src++;
					if(c != 'd' && c != 'i')
						break;

					short sh_case = km_va_arg(args, short);
					km_nitoa((int)sh_case, buffer, length, 10);
					length += km_strlen(buffer + length) - 1;
					break;
				}

				case 'i' : 
				{
					int d_case = km_va_arg(args, int);
					km_nitoa(d_case, buffer, length, 10);
					length += km_strlen(buffer + length) - 1;
					break;
				}

				case 'X' :
				case 'x' :
				{
					int d_case = km_va_arg(args, int);
					km_nitoa(d_case, buffer, length, 16);
					length += km_strlen(buffer + length) - 1;
					break;
				}

				case 'd' :
				case 'F' :
				case 'f' :
				{
					double f_case = km_va_arg(args, double);
					km_nftoa(f_case, buffer, length, 4);
					length += km_strlen(buffer + length) - 1;
					break;
				}
				
				case 'p' :
				{
					unsigned long int p_case = (unsigned long int)km_va_arg(args, void*);
					km_stradd(buffer, "0x");
					km_nlltoa(p_case, buffer, length + 2, 16);
					length += km_strlen(buffer + length) - 1;
					break;
				}
				
				default : break;
			}
		}
		else
		{
			buffer[length] = c;
			length++;
		}
	}
	return buffer;
}
