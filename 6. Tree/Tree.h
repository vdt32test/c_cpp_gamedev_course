#pragma once
typedef int DataType;

enum Result
{
    R_OK,
    R_NULL_PTR_ERROR,
    R_BAD_ALLOC,
    R_NO_ELEMENT
};

struct TreeNode
{
    DataType data;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct Tree
{
    struct TreeNode *root;
};


enum Result constructor(struct Tree *tree);
enum Result destructor(struct Tree *tree);
enum Result push(struct Tree *tree, DataType data);
enum Result find(struct Tree *tree, const DataType data, struct TreeNode **ret_node);
