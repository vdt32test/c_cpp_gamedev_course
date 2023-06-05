#include <stdio.h>
#include <stdlib.h>
#include "list.h"


int main()
{
    struct List the_list;
    constructor(&the_list);

    DataType el = 2;

    push_front(&the_list, &el);
    push_front(&the_list, &el);
    push_front(&the_list, &el);
    push_front(&the_list, &el);
    push_front(&the_list, &el);
    push_front(&the_list, &el);
    push_front(&the_list, &el);
    
    destructor(&the_list);
    return EXIT_SUCCESS;
}