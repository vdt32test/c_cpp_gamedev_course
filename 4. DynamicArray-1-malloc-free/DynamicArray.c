#include "DynamicArray.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const char *green_color = "\033[1;32m";
const char *white_color = "\033[1;37m";

enum Result zeroBufferMemory(struct DynamicArray *the_array);
enum Result zeroElementMemory(DataType *element);


enum Result constructor(struct DynamicArray *the_array)
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

    the_array->size = 0;
    the_array->buffer = NULL;
    
    return R_OK;
}

enum Result destructor(struct DynamicArray *the_array)
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

    free(the_array->buffer);

    return R_OK;
}

enum Result push_back(struct DynamicArray *the_array, DataType element)
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

    DataType *tmp = the_array->buffer;
    the_array->buffer = (DataType *)malloc(sizeof(DataType)*(the_array->size+1));
    if(!the_array->buffer)
    {
        the_array->buffer = tmp;
        return R_BAD_ALLOC;
    }

    for(unsigned i = 0; i < the_array->size; i++)
    {
        the_array->buffer[i] = tmp[i];
    }

    the_array->buffer[the_array->size] = element;
    the_array->size++;

    free(tmp);

    return R_OK;
}

enum Result pop_back(struct DynamicArray *the_array)
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

    if(the_array->size == 0)
        return R_BUFFER_UNDERFLOW;

    if(the_array->size == 1)
    {
        free(the_array->buffer);
        the_array->buffer = NULL;
        the_array->size = 0;
        return R_OK;
    }

    DataType *tmp = the_array->buffer;
    the_array->buffer = (DataType *)malloc(sizeof(DataType)*(the_array->size-1));
    if(!the_array->buffer)
    {
        the_array->buffer = tmp;
        return R_BAD_ALLOC;
    }

    for(unsigned i = 0; i < the_array->size-1; i++)
    {
        the_array->buffer[i] = tmp[i];
    }

    the_array->size--;

    free(tmp);

    return R_OK;
}

enum Result print_array_int(struct DynamicArray *the_array)
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

    puts("print_array_int"); 
    for(unsigned i = 0; i < the_array->size; i++)
    {
        printf("  array[%u] = %d\n", i, the_array->buffer[i]);
    }
    puts("");

    return R_OK;
}

enum Result print_array_int_debug(struct DynamicArray *the_array)
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

    printf("DynamicArray 0x%p\n{\n", the_array);
    printf("\tsize = %u\n", the_array->size);
    printf("\tbuffer = 0x%p\n\t{\n", the_array->buffer);

    for(unsigned i = 0; i < the_array->size; i++)
    {
        if(i < the_array->size)
            printf("\t\t>");
        else
            printf("\t\t ");

        printf("buffer[%u] = %d\n", i, the_array->buffer[i]);
    }

    printf("\t}\n}\n");

    return R_OK;
}

enum Result print_array_int_debug_str(struct DynamicArray *the_array, const char *str)
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

    printf("%s>>> %s <<<%s\n", green_color, str, white_color);
    print_array_int_debug(the_array);
    printf("\n");

    return R_OK;
}
