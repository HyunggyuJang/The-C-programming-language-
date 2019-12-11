#include "charAlloc.h"
#include "Alloc.h"

char *(*charAlloc)(int size) = alloc;
void (*freeChar)(char *allocated) = afree;
