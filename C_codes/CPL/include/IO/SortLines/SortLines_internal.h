#ifndef __SORTLINES_INTERNAL_H_
#define __SORTLINES_INTERNAL_H_

#include "common.h"

typedef struct
{
    unsigned int isNumeric : 1;
    unsigned int shouldReverse : 1;
    unsigned int shouldFold : 1;
    unsigned int isDirectory : 1;
} OptionType;

typedef OptionType *Option;

char *SortLines_ParseOption(Option option, char *toBeParsed);

BOOL isFieldOption(char *optionString);

#endif // __SORTLINES_INTERNAL_H_
