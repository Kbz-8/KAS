// kmlib (kbz_8 memory library) project is a mini project for fun.
// 
// AUTHOR: kbz_8
// CREATED: 01/09/2021
// UPDATED: 22/02/2022

#include "kmlib.h"

typedef struct block
{
	size_t size;
	struct block* next;
	struct block* prev;
} block;

static block* head = NULL;
static block* tail = NULL;
static long long gc_leaks_bytes = 0;
static bool is_gc_init = false;
static bool is_cleanup_activated = false;
static size_t __page_size = 0;

void cleanupBlocks()
{
	if(head != NULL || tail != NULL)
	{
		block* ptr = head;
		do
		{
			remove_block(ptr);
			ptr = head;
		} while(tail != NULL || head != NULL);
	}
}

void add_block(block* newBlock)
{
	newBlock->prev = NULL;
	newBlock->next = NULL;
	if(!head)
	{
		head = newBlock;
		tail = head;
	}
	else
	{
		newBlock->prev = tail;
		tail = newBlock;
	}
}

void remove_block(block* delBlock)
{
	if(delBlock == head)
	{
		if(head->next != NULL)
			head = head->next;
		else
		{
			head = NULL;
			tail = head;
		}
	}
	else if(delBlock == tail)
		tail = delBlock->prev;
	else
	{
		delBlock->next->prev = delBlock->prev;
		delBlock->prev->next = delBlock->next;
	}

	delBlock = NULL;
}

void* kml_malloc(size_t size)
{
	void* ptr = NULL;
	block* block_ptr = head;

	block_ptr = mmap(NULL, size + sizeof(block), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, 0, 0);

	if(block_ptr == MAP_FAILED)
	{
		kml_print("\033[0;31m");
		kml_printf("kmlib error: unable to alloc map of size : %d\n", size);
		kml_print("\033[0m");
		return NULL;
	}

	block_ptr->size = size;
	add_block(block_ptr);
	if(!block_ptr)
	{
		kml_print("\033[0;31m");
		kml_printf("kmlib error: unable to alloc %d size\n", size);
		kml_print("\033[0m");
		return NULL;
	}
	ptr = (void*)((unsigned long)block_ptr + sizeof(block));

	if(is_gc_init)
		gc_leaks_bytes += size;
	
	if(!is_cleanup_activated)
	{
		atexit(cleanupBlocks);
		is_cleanup_activated = true;
	}

	return ptr;
}

void* kml_malloc_shared(size_t size)
{
	void* ptr = NULL;
	block* block_ptr = head;

	block_ptr = mmap(NULL, size + sizeof(block), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_SHARED, 0, 0);

	if(block_ptr == MAP_FAILED)
	{
		kml_print("\033[0;31m");
		kml_printf("kmlib error: unable to alloc map of size : %d\n", size);
		kml_print("\033[0m");
		return NULL;
	}

	block_ptr->size = size;
	add_block(block_ptr);

	ptr = (void*)((unsigned long)block_ptr + sizeof(block));

	if(is_gc_init)
		gc_leaks_bytes += size;
	
	if(!is_cleanup_activated)
	{
		atexit(cleanupBlocks);
		is_cleanup_activated = true;
	}

	return ptr;
}

int kml_free(void* ptr)
{
	block* finder = head;
	size_t block_size = sizeof(block); // avoiding redoing sizeof(block) operation at each turn of the loop
	size_t alloc_size = 0;
	do
	{
		if(ptr == (void*)((unsigned long)finder + block_size)) // searching for pointer in blocks chain
		{
			block_size += finder->size;
			alloc_size = finder->size;

			remove_block(finder);
			if(munmap(finder, alloc_size) != 0) // free
			{
				kml_print("\033[0;31m");
				kml_print("kmlib error: unable to unmap pointer\n");
				kml_print("\033[0m");
				ptr = NULL;
				return 0;
			}
			if(is_gc_init)
				gc_leaks_bytes -= alloc_size;
			ptr = NULL;
			return 1; // if pointer was correctly freed
		}

		finder = finder->next;
	} while(finder != tail);
	return 0; // if pointer was not correctly freed
}

void* kml_realloc(void* ptr, size_t size)
{
	if(!ptr)
		return kml_malloc(size);
	block* finder = head;
	void* newPtr = NULL;
	size_t block_size = sizeof(block);
	do
	{
		if(ptr == (void*)((unsigned long)finder + block_size))
		{
			if(size == finder->size)
				return ptr;

			newPtr = kml_malloc(size);

			if(size > finder->size)
				kml_memcpy(newPtr, ptr, finder->size);
			else if(size < finder->size)
				kml_memcpy(newPtr, ptr, size);

			if(!newPtr)
			{
				kml_print("\033[0;31m");
				kml_printf("kmlib error: unable to realloc %d size\n", size);
				kml_print("\033[0m");
				return NULL;
			}
			return newPtr;
		}
	} while(finder != tail);
	return NULL;
}

void* kml_calloc(size_t n, size_t size)
{
	void* ptr = kml_malloc(n * size);
	if(!ptr)
	{
		kml_print("\033[0;31m");
		kml_printf("kmlib error: unable to calloc %d size\n", size);
		kml_print("\033[0m");
		return NULL;
	}
	kml_memset(ptr, 0, n * size);
	return ptr;
}

void* kml_memset(void* ptr, int c, size_t size)
{
	#ifdef KML_MEMSET_AUTO_MALLOC
		if(!ptr)
			ptr = kml_malloc(size);
	#endif

	unsigned char* source = (unsigned char*)ptr;
	while(size--)
	{
		*source++ = (unsigned char)c;
	}
	return ptr;
}

void* kml_memcpy(void* dest, void* src, size_t size)
{	
	#ifdef KML_MEMCPY_AUTO_MALLOC
		if(!dest)
			dest = kml_malloc(size);
	#endif

	unsigned char* p_dest = (unsigned char*)dest;
	const unsigned char* p_src = (unsigned char*)src;

	if(dest != NULL && src != NULL)
	{
		while(size--)
		{
			*p_dest++ = *p_src++;
		}
	}
	return dest;
}

void kml_end_gc()
{
	if(is_gc_init)
	{
		if(gc_leaks_bytes != 0)
		{
			printf("\033[0;35m");
			#ifndef KML_GC_DONT_FREE_LEAKS
				kml_printf("kmlib GC warning: leak of %lld bytes has been detected ! freeing the memory leak [#define KML_GC_DONT_FREE_LEAKS to avoid that]\n", gc_leaks_bytes);
				block* free = head;
				void* ptr = NULL;
				do
				{
					ptr = (void*)((unsigned long)free + sizeof(block));
					if(!kml_free(ptr))
						kml_print("\033[0;31mkmlib GC error: unable to free leak\n");
					free = head;
				} while(head != tail);
			#else
				kml_printf("kmlib GC warning: leak of %lld bytes has been detected ! \n", gc_leaks_bytes);
			#endif
		}
		else
			kml_print("\33[0;32mkmlib GC: no leaks have been detected \n");
		kml_print("\033[0m");
		is_gc_init = false;
	}
}

void kml_init_gc()
{
	gc_leaks_bytes = 0;
	is_gc_init = true;
	atexit(kml_end_gc);
}

size_t kml_strlen(const char* str)
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

void kml_strcpy(char* dest, const char* src)
{
	kml_memcpy(dest, src, kml_strlen(src) - 1);
}

void kml_stradd(char* dest, const char* src)
{
	kml_memcpy(dest + kml_strlen(dest) - 1, src, kml_strlen(src) - 1);
}

void kml_print(const char* out)
{
	int fd = open("/home/bilbo/Documents/Programmation/c/kmlib/out/out", O_APPEND); // TODO : relative path
	size_t map_size = kml_strlen(out);

	char* out_buffer = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_FILE | MAP_PRIVATE, fd, 0);

	if(out_buffer == MAP_FAILED)
		return;

	kml_memcpy((void*)out_buffer, (void*)out, map_size);
	fwrite(out_buffer, 1, map_size, stdout);

	close(fd);
}

void kml_println(const char* out)
{
	int fd = open("/home/bilbo/Documents/Programmation/c/kmlib/out/out", O_APPEND); // TODO : relative path
	size_t map_size = kml_strlen(out);

	char* out_buffer = mmap(NULL, map_size + 1, PROT_READ | PROT_WRITE, MAP_FILE | MAP_PRIVATE, fd, 0);

	if(out_buffer == MAP_FAILED)
		return;

	kml_memcpy((void*)out_buffer, (void*)out, map_size);
	out_buffer[map_size] = '\n';
	fwrite(out_buffer, 1, map_size + 1, stdout);

	close(fd);
}

void kml_printf(const char* out, ...)
{
	kml_va_list args = NULL;
	kml_va_start(args, out);

	char* buffer = kml_vsprintf(out, args);

	kml_va_end(args);

	int fd = open("/home/bilbo/Documents/Programmation/c/kmlib/out/out", O_APPEND); // TODO : relative path
	size_t map_size = kml_strlen(buffer);

	char* out_buffer = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_FILE | MAP_PRIVATE, fd, 0);

	if(out_buffer == MAP_FAILED)
		return;

	kml_memcpy((void*)out_buffer, (void*)buffer, map_size);

	fwrite(out_buffer, 1, map_size, stdout);

	close(fd);
	kml_free(buffer);
}

void kml_strrev(char* arr, int start, int end)
{
	// Fast string inversion

	if(start >= end)
		return;
	if(*(arr + end) == '\0')
		end--;

	// Fast variable inversion with XOR operation
	// 
	// a = a ^ b
	// b = a ^ b
	// a = a ^ b
	*(arr + start) = *(arr + start) ^ *(arr + end);
	*(arr + end)   = *(arr + start) ^ *(arr + end); // a bit tricky
	*(arr + start) = *(arr + start) ^ *(arr + end);
	
	kml_strrev(arr, start + 1, end - 1);
}

char* kml_nitoa(int num, char* dest, int pos, int base)
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
	kml_strrev(dest, pos, i - 1);

	return dest;
}

char* kml_itoa(int num, char* dest, int base)
{
	return kml_nitoa(num, dest, 0, base);
}

char* kml_nlltoa(long long num, char* dest, int pos, int base)
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
	kml_strrev(dest, pos, i - 1);

	return dest;
}

char* kml_lltoa(long long num, char* dest, int base)
{
	return kml_nlltoa(num, dest, 0, base);
}

#define MAX_PRECISION 10
static const double rounders[MAX_PRECISION + 1] = {
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

char* kml_nftoa(double num, char* dest, int pos, int precision)
{
	int start_pos = 0;
	char c = 0;
	long int_part = 0;
	size_t length = pos;

	if(precision > MAX_PRECISION)
		precision = MAX_PRECISION;

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
		kml_strrev(dest, start_pos, length);
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

char* kml_ftoa(double num, char* dest, int precision)
{
	kml_nftoa(num, dest, 0, precision);
}

char* kml_vsprintf(const char* src, kml_va_list args)
{
	char c = 0;
	size_t max_length = kml_strlen(src) + 256;
	char* buffer = (char*)kml_malloc(sizeof(char) * max_length);
	size_t length = 0;

	while(c = *src++)
	{
		if(length > max_length)
		{
			max_length += 256;
			buffer = (char*)kml_realloc(buffer, max_length);
		}

		if(c == '%')
		{
			switch(c = *src++)
			{
				case '%' : buffer[length] = '%'; length++; break;
				
				case 'c' : buffer[length] = kml_va_arg(args, char); length++; break;
				
				case 's' : char* s_case = kml_va_arg(args, char*); kml_stradd(buffer, s_case); length += kml_strlen(s_case) - 1; s_case = NULL; break;
				
				case 'l':
				{
					c = *src++;
					if(c != 'd' && c != 'i')
					{
						c = *src++;
						if(c != 'd' && c != 'i')
							break;
					}
					long long ll_case = kml_va_arg(args, long long);
					kml_nlltoa(ll_case, buffer, length, 10);
					length++;
					while(ll_case /= 10)
						length++;
					break;

				case 'h':
				{
					c = *src++;
					if(c != 'd' && c != 'i')
						break;

					short sh_case = kml_va_arg(args, short);
					kml_nitoa((int)sh_case, buffer, length, 10);
					length++;
					while(ll_case /= 10)
						length++;
					break;
				}
				}

				case 'i' : 
				case 'd' :
				{
					int d_case = kml_va_arg(args, int);
					kml_nitoa(d_case, buffer, length, 10);
					length++;
					while(d_case /= 10)
						length++;
					break;
				}

				case 'X' :
				case 'x' :
				{
					int d_case = kml_va_arg(args, int);
					kml_nitoa(d_case, buffer, length, 16);
					length += kml_strlen(buffer + length) - 1;
					break;
				}

				case 'F' :
				case 'f' :
				{
					double f_case = kml_va_arg(args, double);
					int precision = 4;
					kml_nftoa(f_case, buffer, length, precision);
					while(precision--)
						f_case *= 10;

					long length_manager = (long)f_case;
					length++;
					while(length_manager /= 10)
						length++;
					break;
				}
				
				case 'p' : break;
				
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

