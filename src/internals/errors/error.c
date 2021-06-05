#include <internals/errors/error.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    InitValueInfoLength = 2
} ErrorsInitValue;

static const char* ERROR_INFO[][InitValueInfoLength] = {
    [ErrorFileNotFound] = {"FileNotFound", "Could not open file -"},
    [ErrorParsingFailed] = {"ParsingFailed", "Can't convert this document."},
    [ErrorIndexOutOfRange] = {"IndexOutOfRange", "Index was out of range in -"},
    [ErrorOutOfMemory] = {"OutOfMemory", "Could not allocate enough memory via -"},
    [ErrorUnknownArg] = {"UnknownArgument", "You entered an unknown argument."}};

void throw_error(TypeOfError ex, const char* msg)
{
    fprintf(stderr, "\n\033[31mError\033[0m: %s.\n", ERROR_INFO[ex][0]);
    fprintf(stderr, "%s: ", "\033[31mAddition information\033[0m");
    msg ? fprintf(stderr, "%s %s.\n", ERROR_INFO[ex][1], msg) : fprintf(stderr, "%s.\n", "Not provided");
    exit(ex);
}