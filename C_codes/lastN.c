#include <stdlib.h>
#include <stdio.h>
#include "ex5_13.h"

enum {DESTROYED = -1, UNDEFINED = 0, DEFINED = 1};

static char **lastN;            /* pointer array holding last n lines */
static char *flags;             /* flags for above array whether it defined or destroyed */
static int next = 0;            /* index to be set next */
static int wrapped = -1;        /* the index holding wrapped line */
static int size;                /* size of pointer array */

void setLastN(int n) {
    lastN = malloc(sizeof(char *) * n);
    flags = malloc(sizeof(char) * n);
    size = n;
    while (n-- > 0)             /* initialize flags */
        flags[n] = UNDEFINED;
    n = size;
    while (n-- > 0)             /* initialize pointer array */
        lastN[n] = NULL;
}

void insertLast(char *p, int isWrapped) {
    if (isWrapped)
        wrapped = next;
    else if (wrapped == next)
        wrapped = -1;           /* need to unset wrapped */
    lastN[next] = p, flags[next++] = DEFINED;
    if (next == size)           /* need to wrap */
        next = 0;
}

int heldBy(char *p) {
    int i = size;
    while (i-- > 0)
        if (lastN[i] == p)
            return i;
    return -1;

}

void destroyIfHeld(char *p) {
    int i = heldBy(p);
    if (i < 0)
        return;
    flags[i] = DESTROYED;
}

char existDestroyed(void) {
    int i = size;
    while (i-- > 0)
        if (flags[i] == DESTROYED)
            return 1;
    return 0;
}

void writeLineWrappedN(void) {
    int i = next;
    do {
        if (flags[i] != DEFINED)
            continue;
        if (i == wrapped)
            printf("%s%s\n", lastN[i], firstPointer());
        else
            printf("%s\n", lastN[i]);
    } while ((i = (i + 1) % size) != next); /* for wrapping case */
}

void inspectLastN(void) {
    int i = size;
    while (i-- > 0)
        if (i == wrapped)
            printf("current line is wrapped one. The first one is \n%s\nat heap index %d\nand the rest is\n%s\n",
                   lastN[i], lastN[i] - firstPointer(), firstPointer());
        else
            printf("%s\nis stored at heap index %d\n", lastN[i], lastN[i] - firstPointer());
}

void freeLastN(void) {
    free(lastN);
    free(flags);
}
