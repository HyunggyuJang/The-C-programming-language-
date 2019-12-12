#include "SortLines_internal.h"

int tieBreakUsingNextField(char *s1, char *s2)
{
    if (!SortLines_HaveNextFieldOption())
    {
        SortLines_SetFieldOption();
        return 0;
    }
    SortLines_NextFieldOption();
    setCompareProcedure();
    return compare(s1, s2);
}

int noTieBreak(char *s1, char *s2)
{
    return 0;
}
