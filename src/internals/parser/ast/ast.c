#include <internals/generic/array/array.h>
#include <internals/memext/memext.h>
#include <internals/parser/ast/ast.h>

TNode* init_tnode(TypeOfTNode type, String* head, String* content, bool nesting)
{
    TNode* node = memalloc(sizeof(TNode));
    node->type = type;
    node->head = head;
    node->content = content;
    node->nesting = nesting;
    node->parrent = NULL;
    node->children = init_array(TNode*, 4);
    return node;
}

void free_tnode(TNode* node)
{
    if (node)
    {
        if (node->head)
        {
            cs_free(node->head);
        }
        if (node->content)
        {
            cs_free(node->content);
        }
        if (node->children)
        {
            for (size_t i = 0; i < get_array_length(node->children); ++i)
            {
                free_tnode(node->children[i]);
            }
            free_array(node->children);
        }
        free(node);
    }
}

TNode* get_last_tnode(TNode* parrent)
{
    return parrent->children ? parrent->children[get_array_length(parrent->children) - 1] : NULL;
}

void add_tnode(TNode* parrent, TNode* child)
{
    child->parrent = parrent;
    add_array((parrent->children), child);
}

void remove_tnode(TNode* parrent, size_t index)
{
    remove_array(parrent->children, index);
}

bool is_root_tnode(TNode* node)
{
    return node->parrent == NULL;
}

bool is_leaf_tnode(TNode* node)
{
    return get_array_length(node->children) == 0;
}

size_t get_tnode_lvl(TNode* node)
{
    return (is_root_tnode(node)) ? 0 : get_tnode_lvl(node->parrent) + 1;
}
