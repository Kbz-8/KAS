// kmlib (kbz_8 memory library) project is a mini project for fun.
// 
// AUTHOR: kbz_8
// CREATED: 18/05/2022
// UPDATED: 18/05/2022

typedef void (*exit_fn)(void);

typedef struct
{
    unsigned int num_of_func;
    exit_fn functions[32];
} __exit_func_list;

static __exit_func_list __main_exit_func_list = { 0, NULL };

void kml_assert(int cond)
{
    if(!cond)
        exit()
}

void kml_exit(int status)
{

}

int kml_atexit(void (*func)(void))
{
    kml_assert(func != NULL);
    __main_exit_func_list.functions[__main_exit_func_list.num_of_func] = func;
    __main_exit_func_list.num_of_func++;
}
