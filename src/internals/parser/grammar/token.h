#ifndef TOKEN_H
#define TOKEN_H

#include <internals/cstrings/strings.h>

typedef enum
{
    TokenLineBreak,
    TokenUnderscore,
    TokenAsterisk,
    TokenBacktick,
    TokenEquals,
    TokenMinus,
    TokenPlus,
    TokenOPAngleBracket,
    TokenLattice,
    TokenExclamationMark,
    TokenOPSquareBracket,
    TokenCLAngleBracket,
    TokenSpace,
    TokenCLSquareBracket,
    TokenOPBracket,
    TokenCLBracket,
    TokenNumber,
    TokenText
} TypeOfToken;

typedef struct
{
    TypeOfToken type;
    String* value;
    bool op;
} Token;

#endif