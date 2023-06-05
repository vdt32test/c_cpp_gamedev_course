#include <stdlib.h>
#include <stdio.h>
#include "DynamicArray.h"


int main()
{
    struct DynamicArray the_array;
    print_array_int_debug_str(&the_array, "created struct");

    constructor(&the_array);
    print_array_int_debug_str(&the_array, "constructor");

    push_back(&the_array, 42);
    push_back(&the_array, 1);
    push_back(&the_array, 4);
    push_back(&the_array, 8);
    push_back(&the_array, 9);
    push_back(&the_array, 6);
    print_array_int_debug_str(&the_array, "push_back");

    delete(&the_array, 3);
    print_array_int_debug_str(&the_array, "delete");

    insert(&the_array, 2, 10);
    print_array_int_debug_str(&the_array, "insert");

    destructor(&the_array);
    print_array_int_debug_str(&the_array, "destructor");

    return EXIT_SUCCESS;
}
