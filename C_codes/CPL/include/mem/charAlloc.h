#ifndef __CHARALLOC_H_
#define __CHARALLOC_H_

extern char *(*charAlloc)(int size);
extern void (*freeChar)(char *allocated);

#endif // __CHARALLOC_H_
