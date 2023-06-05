#include <stdlib.h>
#include <stdio.h>
#include "DynamicArray.h"


#define DBG_CALL(func_call)                             \
{                                                       \
    enum Result result = func_call;                     \
    if(result != R_OK)                                  \
    {                                                   \
        printf("%s: %d: "#func_call": error: %d\n",     \
        __FILE__, __LINE__, result);                    \
        exit(EXIT_FAILURE);                             \
    }                                                   \
}


int main()
{
    struct DynamicArray the_array;

    DBG_CALL(constructor(&the_array));
    DBG_CALL(print_array_int_debug_str(&the_array, "constructor"));

    for(int i = 0; i < 2; i++)
    {
        DBG_CALL(push_back(&the_array, 42));
        DBG_CALL(print_array_int_debug_str(&the_array, "push_back"));
        DBG_CALL(push_back(&the_array, 1));
        DBG_CALL(print_array_int_debug_str(&the_array, "push_back"));
        DBG_CALL(push_back(&the_array, 4));
        DBG_CALL(print_array_int_debug_str(&the_array, "push_back"));
        DBG_CALL(push_back(&the_array, 8));
        DBG_CALL(print_array_int_debug_str(&the_array, "push_back"));
        DBG_CALL(push_back(&the_array, 9));
        DBG_CALL(print_array_int_debug_str(&the_array, "push_back"));
        DBG_CALL(push_back(&the_array, 6));
        DBG_CALL(print_array_int_debug_str(&the_array, "push_back"));

        /*delete(&the_array, 3);
        print_array_int_debug_str(&the_array, "delete");

        insert(&the_array, 2, 10);
        print_array_int_debug_str(&the_array, "insert");*/

        DBG_CALL(pop_back(&the_array));
        DBG_CALL(print_array_int_debug_str(&the_array, "pop_back"));
        DBG_CALL(pop_back(&the_array));
        DBG_CALL(print_array_int_debug_str(&the_array, "pop_back"));
        DBG_CALL(pop_back(&the_array));
        DBG_CALL(print_array_int_debug_str(&the_array, "pop_back"));
        DBG_CALL(pop_back(&the_array));
        DBG_CALL(print_array_int_debug_str(&the_array, "pop_back"));
        DBG_CALL(pop_back(&the_array));
        DBG_CALL(print_array_int_debug_str(&the_array, "pop_back"));
        DBG_CALL(pop_back(&the_array));
        DBG_CALL(print_array_int_debug_str(&the_array, "pop_back"));
    }

    DBG_CALL(destructor(&the_array));

    return EXIT_SUCCESS;
}
