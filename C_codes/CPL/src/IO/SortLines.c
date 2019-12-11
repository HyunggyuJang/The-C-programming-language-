#include "SortLines.h"
#include "Readlines.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>             /* atof */
#include "QuickSort.h"
#include "Utils.h"

static char *linePointers[MAXLINES];

typedef struct
{
    unsigned int isNumeric : 1;
    unsigned int shouldReverse : 1;
    unsigned int shouldFold : 1;
    unsigned int isDirectory : 1;
} OptionType;

typedef struct
{
    OptionType option;
    unsigned int startField;
    unsigned int endField;
} FieldOption;

static OptionType currentOption;
static unsigned int startField;
static unsigned int endField;


static FieldOption *optionsHead;
static FieldOption *optionsTail;
static FieldOption *currentOptionp;

void SortLines_ParseCommandline(int argc, char *argv[])
{
    int c;

    currentOption.isNumeric = currentOption.shouldReverse
        = currentOption.shouldFold = currentOption.isDirectory = 0;

    optionsHead = optionsTail = 0;

    currentOptionp = (FieldOption *) &currentOption;

    while (--argc > 0 && (*++argv)[0] == '-')
    {
        if ((c = *++argv[0]) == 'k')
        {
            if (!optionsHead)
            {
                optionsHead = (FieldOption *) malloc(2 * sizeof (FieldOption));
                memset(optionsHead, 0, sizeof (FieldOption));
                currentOptionp = optionsHead;
                optionsTail = optionsHead + 1;
            }
            else
            {
                int size = 0;
                for (FieldOption *ptmp = optionsHead; ptmp != optionsTail; ++ptmp)
                    size++;
                optionsHead = (FieldOption *)
                    (realloc(optionsHead, sizeof (FieldOption) * (size + 2)));
                currentOptionp = optionsHead + size;
                memset(currentOptionp, 0, sizeof (FieldOption));
                optionsTail = optionsHead + size + 1;
            }
            if (!((c = *++argv[0]) && isdigit(c)))
            {
                FormatOutput("sortLines: illegal field option %c, expected integer\n",
                             c);
                continue;
            }

            do
            {
                currentOptionp->startField = 10 * currentOptionp->startField + c - '0';
            } while (isdigit(c = *++argv[0]));
        }

        for (; c; c = *++argv[0]) {
            switch (c) {
                case 'n':
                    currentOptionp->option.isNumeric = 1;
                    break;
                case 'r':
                    currentOptionp->option.shouldReverse = 1;
                    break;
                case 'f':
                    currentOptionp->option.shouldFold = 1;
                    break;
                case 'd':
                    currentOptionp->option.isDirectory = 1;
                    break;
                default:
                    if (c == ',' && currentOptionp->startField)
                        goto ParseTheRestOfField;
                    FormatOutput("sortLines: unsupported option %c\n", c);
            }
        }

        continue;

    ParseTheRestOfField:
        while (isdigit(c = *++argv[0]))
            currentOptionp->endField = 10 * currentOptionp->endField + c - '0';
        if (c)
            FormatOutput("sortLines: illegal field option %c, expected none\n",
                         c);
        continue;
    }

    if (argc > 0)
        FormatOutput("Usage: sortLines -n -r\n");
    if (optionsHead)
        currentOptionp = optionsHead;
}

void SortLines_SetFieldOption(void)
{
    currentOptionp = optionsHead;
}

void SortLines_NextFieldOption(void)
{
    ++currentOptionp;
}

BOOL SortLines_HaveNextFieldOption(void)
{
    return currentOptionp + 1 != optionsTail;
}

void SortLines_Destroy(void)
{
    if (optionsHead)
        free(optionsHead);
}

BOOL SortLines_IsNumeric(void)
{
    return currentOptionp->option.isNumeric;
}

BOOL SortLines_ShouldReverse(void)
{
    return currentOptionp->option.shouldReverse;
}

BOOL SortLines_ShouldFold(void)
{
    return currentOptionp->option.shouldFold;
}

BOOL SortLines_IsDirectoryOrder(void)
{
    return currentOptionp->option.isDirectory;
}

unsigned int SortLines_StartField(void)
{
    return currentOptionp->startField;
}

unsigned int SortLines_EndField(void)
{
    return currentOptionp->endField;
}

int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    if (v1 > v2)
        return 1;
    return 0;
}

static int (*compareProc)(char *s1, char *s2);
static void (*preProcessors[3])(char *to, char *from);
static int (*postProcessor)(int processed);
static int (*tieBreaker)(char *s1, char *s2);

static void preProcess(char *dest, char *source)
{
    int offset = 0;
    do
    {
        (preProcessors[offset])(dest, source);
        source = dest;
    } while (preProcessors[++offset]);
}

static int compare(char *s1, char *s2)
{
    static char localS1[MAXLEN];
    static char localS2[MAXLEN];

    preProcess(localS1, s1);
    preProcess(localS2, s2);

    int resultValue =  postProcessor(compareProc(localS1, localS2));
    if (resultValue)
        return resultValue;
    else
        return tieBreaker(s1, s2);
}

static void toLowers(char *destination, char *source)
{
    while ((*destination++ = tolower(*source++)))
        ;
}

static void chooseField(char *destination, char *source)
{
    int startField = currentOptionp->startField;
    int endOffset = currentOptionp->endField - currentOptionp->startField;
    for (; isspace(*source); ++source)
        ;
    while (--startField > 0)
    {
        while (!isspace(*source++))
            ;
        for (; isspace(*source); ++source)
            ;
    }
    if (endOffset < 0)
        strcpy(destination, source);
    do
    {
        while (!isspace(*source))
            *destination++ = *source++;
        for (;isspace(*source); ++source)
            ;
        if (endOffset)
            *destination++ = ' ';
        *destination = '\0';
    }
    while (--endOffset >= 0);
}

static void toDirectoryChars(char *destination, char *source)
{
    for (; *source; ++source)
        if (isalnum(*source) || *source == ' ')
            *destination++ = *source;
    *destination = '\0';
}

static int invertOutput(int processed)
{
    return -processed;
}

static int idendity(int processed)
{
    return processed;
}

static void setCompareProcedure(void);

static int tieBreakUsingNextField(char *s1, char *s2)
{
    if (!SortLines_HaveNextFieldOption())
    {
        SortLines_SetFieldOption();
        return 0;
    }
    SortLines_NextFieldOption();
    setCompareProcedure();
    return compare(s1, s2);
}

static int noTieBreak(char *s1, char *s2)
{
    return 0;
}

static void setCompareProcedure(void)
{
    int i = 0;
    if (SortLines_StartField())
        preProcessors[i++] = chooseField;

    if (SortLines_IsDirectoryOrder())
        preProcessors[i++] = toDirectoryChars;

    if (SortLines_ShouldFold())
        preProcessors[i++] = toLowers;

    if (i)
        preProcessors[i] = 0;
    else
    {
        preProcessors[0] = (void (*)(char *, char *)) strcpy;
        preProcessors[1] = 0;
    }

    compareProc = SortLines_IsNumeric() ? numcmp : (int (*)(char *, char *))strcmp;

    postProcessor = SortLines_ShouldReverse() ? invertOutput : idendity;

    tieBreaker = optionsHead ? tieBreakUsingNextField : noTieBreak;
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
