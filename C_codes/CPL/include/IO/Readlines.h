#ifndef D_Readlines_H
#define D_Readlines_H

/**********************************************************
 *
 * Readlines is responsible for ...
 *
 **********************************************************/

#define MAXLEN 1000
enum { ERR = -1 };
int readlines(char **linePointers, int limitNumberOfLines);
void writelines(char **linePointers, int limitNumberOfLines);

#endif  /* D_FakeReadlines_H */
