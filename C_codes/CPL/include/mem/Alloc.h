#ifndef D_Alloc_H
#define D_Alloc_H

/**********************************************************
 *
 * Alloc is responsible for simple dynamic allocation
 *
 **********************************************************/
#define ALLOCSIZE 10000

char *alloc(int);
void afree(char *);
void areset(void);

#endif  /* D_FakeAlloc_H */
