#ifndef AST_H
#define AST_H

#include <internals/cstrings/strings.h>

typedef enum
{
    NodeBody,
    NodeSection,
    NodeHorizontalLine,
    NodeBreakLine,
    NodePre,
    NodeOList,
    NodeUOList,
    NodeHeadingInline,
    NodeHeadingUnderline,
    NodeBlockquote,
    NodeInlineCode,
    NodeEmphasis,
    NodeImage,
    NodeLink,
    NodeListItem,
    NodeCode,
    NodeAlt,
    NodeSrc,
    NodeParagraph,
    NodeSpan,
} TypeOfTNode;

typedef struct _tnode
{
    struct
    {
        String* head;
        String* content;
        size_t offset;
        TypeOfTNode type;
        bool nesting;
    };
    struct _tnode* parrent;
    struct _tnode** children;
} TNode;

TNode* init_tnode(TypeOfTNode type, String* head, String* content, bool nesting);

TNode* get_last_tnode(TNode* parrent);

void free_tnode(TNode* root);

void add_tnode(TNode* parrent, TNode* child);

void remove_tnode(TNode* parrent, size_t index);

bool is_root_tnode(TNode* node);

bool is_leaf_tnode(TNode* node);

size_t get_tnode_lvl(TNode* node);

#endif