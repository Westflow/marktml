#include <internals/generic/array/array.h>
#include <internals/parser/ast/ast-visualizator.h>

void print_tnode(TNode* node, FILE* out)
{
    if (node)
    {
        fprintf(out, "%zu  | ", get_tnode_lvl(node));
        for (size_t i = 0; i < get_tnode_lvl(node); ++i)
        {
            fprintf(out, "%s", " ");
        }
        if (node->head)
        {
            fprintf(out, "%s", cs_raw(node->head));
        }
        if (node->content)
        {
            fprintf(out, "%s", cs_raw(node->content));
        }
        fprintf(out, "%s", "\n");
        for (size_t i = 0; i < get_array_length(node->children); ++i)
        {
            print_tnode(node->children[i], out);
        }
    }
}