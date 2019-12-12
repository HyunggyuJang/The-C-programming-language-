#include "SortLines.h"
#include "Readlines.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>             /* atof */
#include "QuickSort.h"
#include "Utils.h"
#include "common.h"

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

static FieldOption *optionsHead;
static FieldOption *optionsTail;
static FieldOption *currentOptionp;

static char *parseNonFieldOptions(OptionType *option, char *toBeParsed)
{
    for (; *toBeParsed; ++toBeParsed) {
        switch (*toBeParsed) {
            case 'n':
                option->isNumeric = 1;
                break;
            case 'r':
                option->shouldReverse = 1;
                break;
            case 'f':
                option->shouldFold = 1;
                break;
            case 'd':
                option->isDirectory = 1;
                break;
            default:
                return toBeParsed;
        }
    }
    return toBeParsed;
}

BOOL isFieldOption(char *optionString)
{
    return (*optionString == 'k');
}

void FieldOption_Initialize(void)
{
    optionsHead = optionsTail = 0;
}

BOOL FieldOption_IsCreated(void)
{
    return optionsHead;
}

void FieldOption_Create(void)
{
    optionsHead = (FieldOption *) malloc(2 * sizeof (FieldOption));
    memset(optionsHead, 0, sizeof (FieldOption));
    currentOptionp = optionsHead;
    optionsTail = optionsHead + 1;
}

void FieldOption_Extend(void)
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

char *FieldOption_ParseStartField(char *optionString)
{
    if (!isdigit(*optionString))
    {
        FormatOutput("sortLines: illegal field option %c, expected integer\n",
                     *optionString);
        return NULL;
    }

    do
    {
        currentOptionp->startField =
            10 * currentOptionp->startField + *optionString - '0';
    } while (isdigit(*++optionString));

    return optionString;
}

void FieldOption_ParseEndField(char *optionString)
{
    if (!isdigit(*optionString))
    {
        FormatOutput("sortLines: illegal field option %c, expected integer\n",
                     *optionString);
        return;
    }

    do
    {
        currentOptionp->endField =
            10 * currentOptionp->endField + *optionString - '0';
    } while (isdigit(*++optionString));
    if (*optionString)
        FormatOutput("sortLines: illegal field option %c, expected none\n",
                     *optionString);
}

void FieldOption_Parse(char *optionString)
{
    if (FieldOption_IsCreated())
        FieldOption_Extend();
    else
        FieldOption_Create();
    optionString = FieldOption_ParseStartField(optionString);

    if (!optionString)
        return;

    optionString = parseNonFieldOptions(&currentOptionp->option, optionString);

    if (!*optionString)
        return;

    if (*optionString != ',')
    {
        FormatOutput("sortLines: unsupported option %c\n", *optionString);
        return;
    }

    FieldOption_ParseEndField(++optionString);
}

void initializeParsedOptions(void)
{
    memset(&currentOption, 0, sizeof(OptionType));
    FieldOption_Initialize();
}

void SortLines_ParseCommandline(int argc, char *argv[])
{
    int c;

    initializeParsedOptions();

    currentOptionp = (FieldOption *) &currentOption;

    while (--argc > 0 && (*++argv)[0] == '-')
    {
        if (isFieldOption(++argv[0]))
            FieldOption_Parse(++argv[0]);
        else
        {
            char *unparsedString = parseNonFieldOptions(&currentOption, argv[0]);
            if (*unparsedString)
                FormatOutput("sortLines: unsupported option %c\n", *unparsedString);
        }
    }
    /* ParseOption_HaveUnparsedCommand */
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
static void (*preProcessors[4])(char *to, char *from);
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

/* toLowers ADT */
static void toLowers(char *destination, char *source)
{
    while ((*destination++ = tolower(*source++)))
        ;
}

/* chooseFieldADT */
static int startField;
static int endField;

static void chooseField(char *destination, char *source)
{
    int tStartField = startField;
    int endOffset = endField - startField;
    for (; isspace(*source); ++source)
        ;
    while (--tStartField > 0)
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

static void (*chooseFieldFromRange(int startingField, int endingField))(char *, char *)
{
    startField = startingField;
    endField = endingField;
    return chooseField;
}

/* toDirectoryCharsADT */
static void toDirectoryChars(char *destination, char *source)
{
    for (; *source; ++source)
        if (isalnum(*source) || *source == ' ')
            *destination++ = *source;
    *destination = '\0';
}

/* postProcessor functions */
static int invertOutput(int processed)
{
    return -processed;
}

static int idendity(int processed)
{
    return processed;
}

static void setCompareProcedure(void);

/* tieBreaker functions */
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
        preProcessors[i++] =
            chooseFieldFromRange(currentOptionp->startField,
                                 currentOptionp->endField);


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
