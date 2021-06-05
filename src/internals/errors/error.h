#ifndef ERROR_H
#define ERROR_H

typedef enum
{
    ErrorFileNotFound = 1,
    ErrorParsingFailed,
    ErrorIndexOutOfRange,
    ErrorOutOfMemory,
    ErrorUnknownArg
} TypeOfError;

void throw_error(TypeOfError err, const char* msg);

#endif