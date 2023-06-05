#include "list.h"
#include "stdlib.h"


enum Result constructor(struct List *list)
{
    if(!list)
        return R_NULL_PTR_ERROR;

    list->head = NULL;
    list->tail = NULL;

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
    tmp->prev = NULL;
    tmp->next = list->head;

    if(!list->head)
        list->tail = tmp;
    else
        list->head->prev = tmp;

    list->head = tmp;

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

    if(list->head)
        list->head->prev = NULL;
    else
        list->tail = NULL;

    return R_OK;
}


enum Result push_back(struct List *list, const DataType *element)
{
    if(!list || !element)
        return R_NULL_PTR_ERROR;

    struct ListNode *tmp = (struct ListNode *)malloc(sizeof(struct ListNode));
    if(!tmp)
        return R_BAD_ALLOC;

    tmp->data = *element;
    tmp->next = NULL;
    tmp->prev = list->tail;

    if(!list->tail)
        list->head = tmp;
    else
        list->tail->next = tmp;

    list->tail = tmp;

    return R_OK;
}


enum Result pop_back(struct List *list)
{
    if(!list)
        return R_NULL_PTR_ERROR;

    if(!list->head)
        return R_EMPTY_LIST;

    struct ListNode *tmp = list->tail;
    list->tail = tmp->prev;
    list->tail->next = NULL;
    free(tmp);

    if(list->tail)
        list->tail->next = NULL;
    else
        list->head = NULL;

    return R_OK;
}


enum Result insert_after(struct List *list, struct ListNode *after, const DataType *element)
{
    if(!list || !after || !element)
        return R_NULL_PTR_ERROR;

    struct ListNode *tmp = (struct ListNode *)malloc(sizeof(struct ListNode));
    if(!tmp)
        return R_BAD_ALLOC;

    tmp->data = *element;

    tmp->next = after->next;
    tmp->prev = after;
    after->next = tmp;

    if(tmp->next)
        tmp->next->prev = tmp;

    if(list->tail == tmp->prev)
        list->tail = tmp;

    return R_OK;
}


enum Result erase_after(struct List *list, struct ListNode *after)
{
    if(!list || !after || !after->next)
        return R_NULL_PTR_ERROR;

    struct ListNode *tmp = after->next;
    after->next = tmp->next;
    free(tmp);

    if(list->tail == tmp)
        list->tail = after;

    if(after->next)
        after->next->prev = after;

    return R_OK;
}


enum Result insert(struct List *list, struct ListNode *before, const DataType *element)
{
    if(!list || !before || !element)
        return R_NULL_PTR_ERROR;

    struct ListNode *tmp = (struct ListNode *)malloc(sizeof(struct ListNode));
    if(!tmp)
        return R_BAD_ALLOC;

    tmp->data = *element;

    tmp->prev = before->prev;
    tmp->next = before;
    
    before->prev = tmp;

    if(tmp->prev)
        tmp->prev->next = tmp;

    if(list->head == tmp->next)
        list->head = tmp;

    return R_OK;
}


enum Result erase(struct List *list, struct ListNode *node_to_erase)
{
    if(!list || !node_to_erase)
        return R_NULL_PTR_ERROR;

    if(node_to_erase->prev)
        node_to_erase->prev->next = node_to_erase->next;

    if(node_to_erase->next)
        node_to_erase->next->prev = node_to_erase->prev;

    if(list->tail == node_to_erase)
        list->tail = node_to_erase->prev;

    if(list->head == node_to_erase)
        list->head = node_to_erase->next;

    free(node_to_erase); 

    return R_OK;    
}
