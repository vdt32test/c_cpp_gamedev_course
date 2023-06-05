#pragma once
//#define NDEBUG

#define DEFAULT_CAPACITY 1
typedef int DataType;

enum Result
{
    R_OK,
    R_NULL_PTR_ERROR,
    R_BUFFER_OVERFLOW,
    R_BUFFER_UNDERFLOW,
    R_INDEX_MISMATCH,
    R_ELEMENT_MISSING,
    R_BAD_ALLOC
};

struct DynamicArray
{
    unsigned size;
    unsigned capacity;
    DataType *buffer;
};

enum Result constructor(struct DynamicArray *the_array);
enum Result destructor(struct DynamicArray *the_array);
enum Result push_back(struct DynamicArray *the_array, DataType element);
enum Result pop_back(struct DynamicArray *the_array);

enum Result print_array_int(struct DynamicArray *the_array);
enum Result print_array_int_debug(struct DynamicArray *the_array);
enum Result print_array_int_debug_str(struct DynamicArray *the_array, const char *str);
