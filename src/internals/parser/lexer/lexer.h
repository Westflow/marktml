#ifndef LEXER_H
#define LEXER_H

#include <internals/parser/grammar/token.h>

Token* tokenize(const String* line);

#endif