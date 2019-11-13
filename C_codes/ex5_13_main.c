#include <stdio.h>
#include <ctype.h>              /* for isdigit */
#include <stdlib.h>             /* for atoi */
#include "ex5_13.h"

#define DEFAULTN 10

static int n = DEFAULTN;

void
parseCommand(int argc, char *argv[]) {
    while (--argc > 0 && (*++argv)[0] == '-')
        if (isdigit(*++argv[0]))
            n = atoi(argv[0]);
        else {
            printf("tail: %s is not number, default value used instead\n", argv[0]);
            n = DEFAULTN;
        }
    if (argc) {
        printf("tail: illegal arguments will be ignored\n");
        printf("Usage: tail [-n]\n");
    }
    if (n < 1)                  /* unrealistic value */
        n = DEFAULTN;
}

int
main(int argc, char *argv[])
{
    parseCommand(argc, argv);
    setLastN(n);
    if (readLineWrappedN() == ERROR) {
        printf("error: tail's heap is full with last %d lines\n", n);
        return 0;
    }
    writeLineWrappedN();
    /* inspectLastN(); */
    freeLastN();
    return 0;
}
