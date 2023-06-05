#include "DynamicArray.h"
#include <string.h>
#include <stdio.h>

const char *green_color = "\033[1;32m";
const char *white_color = "\033[1;37m";

enum Result zeroBufferMemory(struct DynamicArray *the_array);
enum Result zeroElementMemory(DataType *element);


enum Result constructor(struct DynamicArray *the_array)
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

    clear(the_array);
    
    return R_OK;
}

enum Result destructor(struct DynamicArray *the_array)
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

#ifndef NDEBUG
    clear(the_array);
#endif // NDEBUG

    return R_OK;
}

enum Result push_back(struct DynamicArray *the_array, DataType element)
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

    if(the_array->size == CAPACITY)
        return R_BUFFER_OVERFLOW;

    the_array->size++;
    the_array->buffer[the_array->size-1] = element;

    return R_OK;
}

enum Result pop_back(struct DynamicArray *the_array)
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

    if(the_array->size == 0)
        return R_BUFFER_UNDERFLOW;

    the_array->size--;

#ifndef NDEBUG
    zeroElementMemory(&the_array->buffer[the_array->size]);
#endif // NDEBUG

    return R_OK;
}

enum Result get_buffer(struct DynamicArray *the_array, DataType **ptr_to_return)
{
    if(!the_array || !ptr_to_return)
        return R_NULL_PTR_ERROR;

    *ptr_to_return = the_array->buffer;

    return R_OK;
}

enum Result get_element(struct DynamicArray *the_array, unsigned index, DataType *element_to_return)
{
    if(!the_array || !element_to_return)
        return R_NULL_PTR_ERROR;

    if(index >= the_array->size)
        return R_INDEX_MISMATCH;

    *element_to_return = the_array->buffer[index];

    return R_OK;
}

enum Result set_element(struct DynamicArray *the_array, unsigned index, DataType element)
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

    if(index >= the_array->size)
        return R_INDEX_MISMATCH;    

    the_array->buffer[index] = element;

    return R_OK;
}

enum Result insert(struct DynamicArray *the_array, unsigned index, DataType element)
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

    if(the_array->size == CAPACITY)
        return R_BUFFER_OVERFLOW;

    if(index > the_array->size)
        return R_INDEX_MISMATCH;

    // for(unsigned i = the_array->size-1; i >= index; i--)
    // {
    //     the_array->buffer[i+1] = the_array->buffer[i];
    // }

    memmove(&the_array->buffer[index+1], &the_array->buffer[index], sizeof(DataType)*(the_array->size - index));
    the_array->size++;
    the_array->buffer[index] = element;

    return R_OK;
}

enum Result delete(struct DynamicArray *the_array, unsigned index)
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

    if(!the_array->size)
        return R_BUFFER_UNDERFLOW;

    if(index >= the_array->size)
        return R_INDEX_MISMATCH;

    // for(unsigned i = index; i < the_array->size-1; i++)
    // {
    //     the_array->buffer[i] = the_array->buffer[i+1];
    // }

    memmove(&the_array->buffer[index], &the_array->buffer[index+1], sizeof(DataType)*(the_array->size - 1 - index));

    the_array->size--;

#ifndef NDEBUG
    zeroElementMemory(&the_array->buffer[the_array->size]);
#endif // NDEBUG

    return R_OK;
}

enum Result clear(struct DynamicArray *the_array)
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

    the_array->size = 0;

#ifndef NDEBUG
    zeroBufferMemory(the_array);
#endif // NDEBUG

    return R_OK;    
}

enum Result assing(struct DynamicArray *the_array, struct DynamicArray the_array2)
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

#ifndef NDEBUG
    clear(the_array);
#endif // NDEBUG

    the_array->size = the_array2.size;
    for(unsigned i = 0; i < the_array->size; i++)
    {
        the_array->buffer[i] = the_array2.buffer[i];
    }

    return R_OK;
}

enum Result find_element(struct DynamicArray *the_array, DataType element_value, unsigned *result_index)
{
    if(!the_array || !result_index)
        return R_NULL_PTR_ERROR;

    for(unsigned i = 0; i < the_array->size; i++)
    {
        if(the_array->buffer[i] == element_value)
        {
            *result_index = i;
            return R_OK;
        }
    }

    return R_ELEMENT_MISSING;
}

enum Result foreach(struct DynamicArray *the_array, enum Result (*func)(DataType *element))
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

    for(unsigned i = 0; i < the_array->size; i++)
    {
        enum Result result = func(&the_array->buffer[i]);
        if(result != R_OK)
            return result;
    }

    return R_OK;
}

enum Result foreach_safe(struct DynamicArray *the_array, enum Result (*func)(DataType *element))
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

    struct DynamicArray tmp_array;

    enum Result result = assing(&tmp_array, *the_array);
    if(result != R_OK)
        return result;

    result = foreach(&tmp_array, func);
    if(result != R_OK)
        return result;

    result = assing(the_array, tmp_array);

    return result;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
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
    printf("\tbuffer = \n\t{\n");

    for(unsigned i = 0; i < CAPACITY; i++)
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


enum Result print_array_char(struct DynamicArray *the_array)
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

    puts("print_array_int"); 
    for(unsigned i = 0; i < the_array->size; i++)
    {
        printf("  array[%u] = %c\n", i, the_array->buffer[i]);
    }
    puts("");

    return R_OK;
}


enum Result print_array_cstr(struct DynamicArray *the_array)
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

    puts("print_array_int"); 
    for(unsigned i = 0; i < the_array->size; i++)
    {
        printf("  array[%u] = %s\n", i, the_array->buffer[i]);
    }
    puts("");

    return R_OK;
}
#pragma GCC diagnostic pop


enum Result zeroBufferMemory(struct DynamicArray *the_array)
{
    if(!the_array)
        return R_NULL_PTR_ERROR;

    memset((void *)the_array->buffer, 0, sizeof(DataType) * CAPACITY);

    return R_OK;
}


enum Result zeroElementMemory(DataType *element)
{
    if(!element)
        return R_NULL_PTR_ERROR;

    memset((void *)element, 0, sizeof(DataType));

    return R_OK;
}
