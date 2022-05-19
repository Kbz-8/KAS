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

void __km_asm_interal_exit(int status);

typedef void (*exit_fn)(void);

typedef struct
{
    unsigned int num_of_func;
    exit_fn functions[32];
} __exit_func_list;

static __exit_func_list __main_exit_func_list = { 0, {} };

#ifdef NDEBUG
    void km_assert(int cond, const char* file, const char* line) {}
#else
    void km_assert(int cond, const char* file, const char* line)
    {
        if(!cond)
        {
            km_printf("assertion failed : %s, %s", file, line);
            km_exit();
        }
    }
#endif

void km_abort()
{
    km_println("kmlib abortion");
    km_exit(-1);
}

void km_exit(int status)
{
    if(__main_exit_func_list.num_of_func > 0)
    {
        while(__main_exit_func_list.num_of_func != 0)
        {
            __main_exit_func_list.functions[__main_exit_func_list.num_of_func - 1]();
            __main_exit_func_list.num_of_func--;
        }
    }
    __km_asm_interal_exit(status);
}

int km_atexit(void (*func)(void))
{
    km_assert(func != NULL, __FILE__, __LINE__);
    __main_exit_func_list.functions[__main_exit_func_list.num_of_func] = func;
    __main_exit_func_list.num_of_func++;
}
