#include "SortLines_internal.h"

/* postProcessor functions */
int invertOutput(int processed)
{
    return -processed;
}

int idendity(int processed)
{
    return processed;
}
