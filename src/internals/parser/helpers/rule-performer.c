#include <internals/generic/array/array.h>
#include <internals/parser/helpers/rule-performer.h>
#include <inttypes.h>
#include <stdarg.h>

#define RULE_TABLE_CAPACITY 5
#define PARSE_FAIL_RESULT NULL

/******************************
 *                            *
 *  Section: Helper functions *
 *                            *
 ******************************/

size_t skip_spaces(size_t index, Token* tokens)
{
    for (; index < get_array_length(tokens); ++index)
    {
        if (tokens[index].type != TokenSpace)
        {
            return index;
        }
    }
    return index;
}

/******************************
 *                            *
 *        End section         *
 *                            *
 ******************************/

/******************************
 *                            *
 *   Section: Rule parsing    *
 *                            *
 ******************************/

static TNode* parse_span(RulePerformer* perf, size_t lim, ...)
{
    TNode* node = init_tnode(NodeSpan, cs_create("<span>"), cs_create(""), false);
    size_t ws_count = 0;
    while (perf->cp < lim && !perf->tokens[perf->cp].op)
    {
        perf->tokens[perf->cp].type == TokenSpace ? (++ws_count) : (ws_count = 0);
        cs_concat(node->content, cs_raw(perf->tokens[perf->cp++].value));
    }
    if (perf->tokens[perf->cp].type == TokenLineBreak)
    {
        if (ws_count >= LimitLowerWhitespaceForBreakLine)
        {
            add_tnode(node, init_tnode(NodeBreakLine, cs_create("<br>"), NULL, false));
            node->nesting = true;
        }
        perf->cp = perf->count;
    }
    return node;
}

/******************************
 *                            *
 *        End section         *
 *                            *
 ******************************/

/******************************
 *                            *
 *      Section: RP main      *
 *                            *
 ******************************/

typedef struct
{
    TNode* (*parse_rule)(RulePerformer* perf, size_t lim, ...);
} RuleFunc;

static const RuleFunc PARSE_TABLE[] = {[RuleUnknown] = {parse_span}};

static TNode* execute(RulePerformer* perf, size_t lim)
{
    if (!perf->tokens[perf->cp].op)
    {
        perf->mode = ModeAvaliableOnlyText;
        return PARSE_TABLE[RuleUnknown].parse_rule(perf, lim);
    }
    return NULL;
}

void init_performer(RulePerformer* perf, Token* tokens, size_t pos)
{
    perf->mode = tokens[pos].op ? ModeAvaliableAll : ModeAvaliableOnlyText;
    perf->tokens = tokens;
    perf->cp = pos;
    perf->count = get_array_length(tokens);
    perf->invoke = &execute;
}

/******************************
 *                            *
 *        End section         *
 *                            *
 ******************************/