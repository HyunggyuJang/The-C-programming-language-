#ifndef D_CharInputSpy_H
#define D_CharInputSpy_H

/**********************************************************
 *
 * CharInputSpy is responsible for ...
 *
 **********************************************************/

#include "CharInput.h"
void CharInputSpy_Create(const char *stdin);
void CharInputSpy_Destroy(void);
int CharInputSpy(void);
int CharInputSpy_NumberOfCalled(void);

#endif  /* D_FakeCharInputSpy_H */
