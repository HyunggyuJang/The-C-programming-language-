#include "SortLines_options.h"
#include <stdlib.h>
#include <ctype.h>
#include "Utils.h"

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
    return (int) optionsHead;
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

void setDefaultCurrentOption()
{
    currentOptionp = (FieldOption *) &currentOption;
}

void parseDefaultOptions(char *toBeParsed)
{
    char *unparsedString = parseNonFieldOptions(&currentOption, toBeParsed);
    if (*unparsedString)
        FormatOutput("sortLines: unsupported option %c\n", *unparsedString);
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
