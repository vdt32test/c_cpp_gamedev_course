#include "list.h"
#include "stdlib.h"


enum Result constructor(struct List *list)
{
    if(!list)
        return R_NULL_PTR_ERROR;

    list->head = NULL;

    return R_OK;
}


enum Result destructor(struct List *list)
{
    if(!list)
        return R_NULL_PTR_ERROR;

    while(list->head)
        pop_front(list);

    return R_OK;
}


enum Result push_front(struct List *list, const DataType *element)
{
    if(!list || !element)
        return R_NULL_PTR_ERROR;

    struct ListNode *tmp = (struct ListNode *)malloc(sizeof(struct ListNode));
    if(!tmp)
        return R_BAD_ALLOC;

    tmp->data = *element;
    tmp->next = list->head;
    list->head = tmp->next;

    return R_OK;
}


enum Result pop_front(struct List *list)
{
    if(!list)
        return R_NULL_PTR_ERROR;

    if(!list->head)
        return R_EMPTY_LIST;

    struct ListNode *tmp = list->head;
    list->head = tmp->next;
    free(tmp);

    return R_OK;
}


enum Result insert_after(struct ListNode *after, const DataType *element)
{
    if(!after || !element)
        return R_NULL_PTR_ERROR;

    struct ListNode *tmp = (struct ListNode *)malloc(sizeof(struct ListNode));
    if(!tmp)
        return R_BAD_ALLOC;

    tmp->data = *element;
    tmp->next = after->next;
    after->next = tmp;    

    return R_OK;
}


enum Result erase_after(struct ListNode *after)
{
    if(!after || !after->next)
        return R_NULL_PTR_ERROR;

    struct ListNode *tmp = after->next;
    after->next = tmp->next;
    free(tmp);

    return R_OK;
}
