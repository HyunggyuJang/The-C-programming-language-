#ifndef D_AllocSpy_H
#define D_AllocSpy_H

/**********************************************************
 *
 * AllocSpy is responsible for ...
 *
 **********************************************************/

#include "charAlloc.h"
#include "Alloc.h"
void AllocSpy_Create(void);
void AllocSpy_Destroy(void);
int AllocSpy_AllocatedSpace(void);
char *AllocSpy_alloc(int size);
void AllocSpy_afree(char *allocated);

#endif  /* D_FakeAllocSpy_H */
