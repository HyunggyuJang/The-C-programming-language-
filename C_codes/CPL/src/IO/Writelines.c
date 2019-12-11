#include "Writelines.h"
#include "Utils.h"

void writelines(char *linePointers[], int numberOfLines)
{
    int currentLineNumber = 0;

    while (numberOfLines > currentLineNumber)
        FormatOutput(linePointers[currentLineNumber++]);
}
