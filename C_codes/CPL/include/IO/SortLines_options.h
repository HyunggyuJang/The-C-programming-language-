#ifndef __SORTLINES_OPTIONS_H_
#define __SORTLINES_OPTIONS_H_

#include "common.h"

void initializeParsedOptions(void);
void setDefaultCurrentOption(void);
BOOL isFieldOption(char *optionString);
void FieldOption_Parse(char *optionString);
void parseDefaultOptions(char *optionString);
BOOL FieldOption_IsCreated(void);

#endif // __SORTLINES_OPTIONS_H_
