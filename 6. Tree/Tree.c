#include "Tree.h"
#include <stdlib.h>

enum Result add_node(struct TreeNode *current_node, struct TreeNode *node_to_add);
enum Result find_node(struct TreeNode *current_node, const DataType data, struct TreeNode **ret_node);
enum Result destructor_node(struct TreeNode *current_node);

enum Result constructor(struct Tree *tree)
{
    if(!tree)
        return R_NULL_PTR_ERROR;

    tree->root = NULL;

    return R_OK;
}

enum Result destructor(struct Tree *tree)
{
    if(!tree)
        return R_NULL_PTR_ERROR;

    return destructor_node(tree->root);
}

enum Result destructor_node(struct TreeNode *current_node)
{
    if(!current_node)
        return R_OK;

    destructor_node(current_node->left);
    destructor_node(current_node->right);

    free(current_node);

    return R_OK;
}

enum Result push(struct Tree *tree, DataType data)
{
    if(!tree)
        return R_NULL_PTR_ERROR;

    struct TreeNode *tmp = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if(!tmp)
        return R_BAD_ALLOC;

    tmp->data = data;
    tmp->left = NULL;
    tmp->right = NULL;

    if(!tree->root) 
    {
        tree->root = tmp;
        return R_OK;
    }

    return add_node(tree->root, tmp); 
}

enum Result add_node(struct TreeNode *current_node, struct TreeNode *node_to_add)
{
    if(node_to_add->data <= current_node->data) 
    {
        if(!current_node->left) 
        {
            current_node->left = node_to_add;
            return R_OK;
        }
        add_node(current_node->left, node_to_add);
    } 
    else
    {
        if(!current_node->right) 
        {
            current_node->right = node_to_add;
            return R_OK;
        }
        add_node(current_node->right, node_to_add);
    }

    return R_OK; 
}

enum Result find(struct Tree *tree, const DataType data, struct TreeNode **ret_node)
{
    if(!tree || !ret_node)
        return R_NULL_PTR_ERROR;

    return find_node(tree->root, data, ret_node); 
}

enum Result find_node(struct TreeNode *current_node, const DataType data, struct TreeNode **ret_node)
{
    if(!current_node)
        return R_NO_ELEMENT;

    if(current_node->data == data)
        *ret_node = current_node;

    if(data < current_node->data) 
        find_node(current_node->left, data, ret_node);
    else
        find_node(current_node->right, data, ret_node);

    return R_OK; 
}