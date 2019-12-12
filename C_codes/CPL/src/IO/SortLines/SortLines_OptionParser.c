#include "SortLines_internal.h"

char *SortLines_ParseOption(Option option, char *toBeParsed)
{
    for (; *toBeParsed; ++toBeParsed)
    {
        switch (*toBeParsed) {
            case 'n':
                option->isNumeric = 1;
                break;
            case 'r':
                option->shouldReverse = 1;
                break;
            case 'f':
                option->shouldFold = 1;
                break;
            case 'd':
                option->isDirectory = 1;
                break;
            default:
                return toBeParsed;
            }
    }
    return toBeParsed;
}
