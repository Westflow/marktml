#include <ctest.h>
#include <internals/generic/array/array.h>
#include <internals/parser/lexer/lexer.h>

CTEST(lexer, tokenize_ops)
{
    String* str = cs_create("\n_*`=-+<#![>~");
    Array(Token) arr = tokenize(str);
    for (size_t i = 0; i < get_array_length(arr); ++i)
    {
        ASSERT_EQUAL(i, arr[i].type);
        ASSERT_TRUE(arr[i].op);
        ASSERT_EQUAL(cs_get(str, i), cs_get(arr[i].value, 0));
        cs_free(arr[i].value);
    }
    cs_free(str);
    free_array(arr);
}

CTEST(lexer, tokenize_not_ops)
{
    String* str = cs_create(" ]()\":");
    Array(Token) arr = tokenize(str);
    for (size_t i = 0; i < get_array_length(arr); ++i)
    {
        ASSERT_EQUAL(i + TokenSpace, arr[i].type);
        ASSERT_FALSE(arr[i].op);
        ASSERT_EQUAL(cs_get(str, i), cs_get(arr[i].value, 0));
        cs_free(arr[i].value);
    }
    cs_free(str);
    free_array(arr);
}

CTEST(lexer, tokenize_text)
{
    String* str = cs_create("qwerty uiop asdf ghjkl zxcvbn\n");
    Array(Token) arr = tokenize(str);
    for (size_t i = 0; i < get_array_length(arr); i += 2)
    {
        ASSERT_EQUAL(TokenText, arr[i].type);
        ASSERT_FALSE(arr[i].op);
        cs_free(arr[i].value);
        cs_free(arr[i + 1].value);
    }
    cs_free(str);
    free_array(arr);
}

CTEST(lexer, tokenize_number_ok)
{
    String* str = cs_create("1. 2. 3. 4. 5. 6. 7. 8. 9. 123456. 12345.\n");
    Array(Token) arr = tokenize(str);
    for (size_t i = 0; i < get_array_length(arr); i += 2)
    {
        ASSERT_EQUAL(TokenNumber, arr[i].type);
        ASSERT_TRUE(arr[i].op);
        cs_free(arr[i].value);
        cs_free(arr[i + 1].value);
    }
    cs_free(str);
    free_array(arr);
}

CTEST(lexer, tokenize_number_fail)
{
    String* str = cs_create("012345.\n");
    Array(Token) arr = tokenize(str);
    ASSERT_EQUAL(TokenText, arr[0].type);
    ASSERT_FALSE(arr[0].op);
    ASSERT_STR("012345.", cs_raw(arr[0].value));
    for (size_t i = 0; i < get_array_length(arr); ++i)
    {
        cs_free(arr[i].value);
    }
    cs_free(str);
    free_array(arr);
}

CTEST(lexer, escape_all_tokens)
{
    String* str = cs_create("\\\n\\_\\*\\`\\=\\-\\+\\<\\#\\!\\[\\>\\~\\ \\]\\(\\)\\\"\\:\\123.\\qwerty\n");
    Array(Token) arr = tokenize(str);
    ASSERT_EQUAL(TokenLineBreak, arr[0].type);
    ASSERT_TRUE(arr[0].op);
    ASSERT_STR("\n", cs_raw(arr[0].value));
    cs_free(arr[0].value);
    size_t i = 1;
    for (; i < TokenSpace; ++i)
    {
        ASSERT_EQUAL(TokenText, arr[i].type);
        ASSERT_FALSE(arr[i].op);
        cs_free(arr[i].value);
    }
    for (; i < get_array_length(arr) - 1; ++i)
    {
        ASSERT_EQUAL(i, arr[i].type);
        cs_free(arr[i].value);
    }
    cs_free(arr[i].value);
    cs_free(str);
    free_array(arr);
}

CTEST(tokenizer, check_empty)
{
    String* str = cs_create("");
    Array(Token) arr = tokenize(str);
    ASSERT_EQUAL(0, get_array_length(arr));
    free_array(arr);
    cs_free(str);
}

CTEST(tokenizer, escape_number)
{
    String* str = cs_create("1\\.\n");
    Array(Token) arr = tokenize(str);
    ASSERT_EQUAL(TokenText, arr[0].type);
    for (size_t i = 0; i < get_array_length(arr); ++i)
    {
        cs_free(arr[i].value);
    }
    free_array(arr);
    cs_free(str);
}

CTEST(tokenizer, escape_escape)
{
    String* str = cs_create("\\\\\n");
    Array(Token) arr = tokenize(str);
    ASSERT_EQUAL(TokenText, arr[0].type);
    for (size_t i = 0; i < get_array_length(arr); ++i)
    {
        cs_free(arr[i].value);
    }
    free_array(arr);
    cs_free(str);
}

CTEST(tokenizer, check_all_single_tokens)
{
    String* str = cs_create("\n_*`=-+<#![>~ ]()\":");
    Array(Token) arr = tokenize(str);
    for (size_t i = 0; i < get_array_length(arr); ++i)
    {
        ASSERT_EQUAL(cs_get(str, i), cs_get(arr[i].value, 0));
        ASSERT_EQUAL((TypeOfToken)i, arr[i].type);
        i < TokenSpace ? ASSERT_TRUE(arr[i].op) : ASSERT_FALSE(arr[i].op);
        cs_free(arr[i].value);
    }
    free_array(arr);
    cs_free(str);
}