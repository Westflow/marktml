#include <ctest.h>
#include <internals/generic/array/array.h>
#include <internals/parser/helpers/rule-performer.h>
#include <internals/parser/lexer/lexer.h>
#include <time.h>

static char* generate_string(char avaliable_chars[], size_t count, size_t length)
{
    srand(time(NULL));
    char* raw = malloc(length + 1);
    for (size_t i = 0; i < length; ++i)
    {
        raw[i] = avaliable_chars[rand() % count];
    }
    raw[length] = 0;
    return raw;
}

static Array(Token) generate_test_data(char* raw_text)
{
    String* str = cs_create(raw_text);
    free(raw_text);
    cs_append(str, '\n');
    Array(Token) tokens = tokenize(str);
    cs_free(str);
    return tokens;
}

static TNode* parse_node(Array(Token) tokens)
{
    RulePerformer perf = {0};
    init_performer(&perf, tokens, 0);
    TNode* node = perf.invoke(&perf, perf.count);
    for (size_t i = 0; i < get_array_length(tokens); ++i)
    {
        cs_free(tokens[i].value);
    }
    free_array(tokens);
    return node;
}

CTEST(rule_parser, only_text)
{
    char text[] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890@$%^&|\\{}? ";
    TNode* node = parse_node(generate_test_data(generate_string(text, sizeof(text), 1000)));
    ASSERT_NOT_NULL(node);
    ASSERT_EQUAL(NodeSpan, node->type);
    free_tnode(node);
}
