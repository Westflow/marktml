#include <internals/generic/array/array.h>
#include <internals/parser/lexer/lexer.h>
#include <inttypes.h>

#define NOT_FOUND_CODE -1

static const char tokens[] = "\n_*`=-+<#![>~ ]()\":";

typedef enum
{
    StateText,
    StateEscape,
    StateOther
} LState;

/******************************
 *                            *
 *  Section: Helper functions *
 *                            *
 ******************************/

static int8_t is_match(char c)
{
    for (int8_t i = 0; i < sizeof(tokens); ++i)
    {
        if (tokens[i] == c)
        {
            return i;
        }
    }
    return NOT_FOUND_CODE;
}

static int8_t is_escapable(char c)
{
    c = is_match(c);
    return (c == TokenLineBreak || c >= TokenSpace) ? c : NOT_FOUND_CODE;
}

static TypeOfToken validate_number(const String* value)
{
    const char* text = cs_raw(value);
    if (text[0] >= '1' && text[0] <= '9')
    {
        size_t i = 1;
        for (; i < cs_length(value) - 1; ++i)
        {
            if (text[i] < '0' || text[i] > '9')
            {
                return TokenText;
            }
        }
        if (text[i] == '.')
        {
            return TokenNumber;
        }
    }
    return TokenText;
}

static inline Token create_token(int8_t code, String* value, bool op)
{
    Token t = {.type = code, .value = cs_clone(value), .op = op};
    return t;
}

static inline void process_text(Array(Token*) tokens, String* value)
{
    if (cs_length(value) > 0)
    {
        TypeOfToken text_type = validate_number(value);
        add_array((*tokens), create_token(text_type, value, text_type == TokenNumber ? true : false));
        cs_clear(value);
    }
}

static inline void process_token(int8_t code, Array(Token*) tokens, String* value, char c)
{
    process_text(&(*tokens), value);
    cs_append(value, c);
    add_array((*tokens), create_token(code, value, code < TokenSpace ? true : false));
    cs_clear(value);
}

/******************************
 *                            *
 *        End section         *
 *                            *
 ******************************/

/******************************
 *                            *
 *    Section: Main lexer     *
 *                            *
 ******************************/

Array(Token) tokenize(const String* line)
{
    Array(Token) token_list = init_array(Token, 4);
    String* value = cs_init(10);
    for (size_t index = 0; index < cs_length(line); ++index)
    {
        char c = cs_get(line, index);
        int8_t code = is_match(c);
        if (c == '\\')
        {
            process_text(&token_list, value);
            c = cs_get(line, ++index);
            code = is_escapable(c);
        }
        code != NOT_FOUND_CODE ? process_token(code, &token_list, value, c) : cs_append(value, c);
    }
    cs_free(value);
    return token_list;
}

/******************************
 *                            *
 *        End section         *
 *                            *
 ******************************/