typedef int DataType;

enum Result
{
    R_OK,
    R_NULL_PTR_ERROR,
    R_BAD_ALLOC,
    R_EMPTY_LIST
};

struct ListNode
{
    DataType data;
    struct ListNode *next;
};

struct List
{
    struct ListNode *head;
};

enum Result constructor(struct List *list);
enum Result destructor(struct List *list);
enum Result push_front(struct List *list, const DataType *element);
enum Result pop_front(struct List *list);
enum Result insert_after(struct ListNode *after, const DataType *element);
enum Result erase_after(struct ListNode *after);