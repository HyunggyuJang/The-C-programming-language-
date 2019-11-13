#include "ex5_13.h"
#include <stdio.h>
void installWrapped(char *p, char *line, int len) {
    len--;
    *p++ = *line++;             /* entry point should not be destroyed */
    while (len-- > 0) {
        if (isLastPointer(p))
            destroyIfHeld(p), *p = '\0', p = firstPointer(); /* break current line */
        destroyIfHeld(p);
        *p++ = *line++;
    }
}
