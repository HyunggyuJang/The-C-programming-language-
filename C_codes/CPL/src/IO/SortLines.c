#include "SortLines.h"
#include "Readlines.h"
#include "QuickSort.h"
#include "Utils.h"
#include "SortLines_options.h"
#include "SortLines_compareSetter.h"

static char *linePointers[MAXLINES];

void SortLines_ParseCommandline(int argc, char *argv[])
{
    initializeParsedOptions();

    setDefaultCurrentOption();

    while (--argc > 0 && (*++argv)[0] == '-')
    {
        if (isFieldOption(++argv[0]))
            FieldOption_Parse(++argv[0]);
        else
            parseDefaultOptions(argv[0]);

    }
    /* ParseOption_HaveUnparsedCommand */
    if (argc > 0)
        FormatOutput("Usage: sortLines -[k%%d]drnf[,\%%d]\n");
    if (FieldOption_IsCreated())
        SortLines_SetFieldOption();
}

int SortLines(void)
{
    int numberOfLinesRead = readlines(linePointers, MAXLINES);

    if (numberOfLinesRead < 0)
    {
        FormatOutput("input too big to sort\n");
        return 1;
    }

    setCompareProcedure();

    quickSort((void **) linePointers, 0,
              numberOfLinesRead - 1,
              (int (*)(void *, void *))
              compare);

    writelines(linePointers, numberOfLinesRead);

    return 0;
}
