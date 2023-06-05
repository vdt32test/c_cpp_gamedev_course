#pragma once
#define NDEBUG

#define CAPACITY 10
typedef int DataType;

enum Result
{
    R_OK,
    R_NULL_PTR_ERROR,
    R_BUFFER_OVERFLOW,
    R_BUFFER_UNDERFLOW,
    R_INDEX_MISMATCH,
    R_ELEMENT_MISSING
};

struct DynamicArray
{
    unsigned size;
    DataType buffer[CAPACITY];
};

enum Result constructor(struct DynamicArray *the_array);
enum Result destructor(struct DynamicArray *the_array);
enum Result push_back(struct DynamicArray *the_array, DataType element);
enum Result pop_back(struct DynamicArray *the_array);
enum Result get_buffer(struct DynamicArray *the_array, DataType **ptr_to_return);
enum Result get_element(struct DynamicArray *the_array, unsigned index, DataType *element_to_return);
enum Result set_element(struct DynamicArray *the_array, unsigned index, DataType element);
enum Result insert(struct DynamicArray *the_array, unsigned index, DataType element);
enum Result delete(struct DynamicArray *the_array, unsigned index);
enum Result clear(struct DynamicArray *the_array);
enum Result assing(struct DynamicArray *the_array, struct DynamicArray the_array2);
enum Result find_element(struct DynamicArray *the_array, DataType element_value, unsigned *result_index);
enum Result foreach(struct DynamicArray *the_array, enum Result (*func)(DataType *element));
enum Result foreach_safe(struct DynamicArray *the_array, enum Result (*func)(DataType *element));

enum Result print_array_int(struct DynamicArray *the_array);
enum Result print_array_int_debug(struct DynamicArray *the_array);
enum Result print_array_int_debug_str(struct DynamicArray *the_array, const char *str);

enum Result print_array_char(struct DynamicArray *the_array);
enum Result print_array_cstr(struct DynamicArray *the_array);
