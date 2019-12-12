#include "SortLines_internal.h"
#include <stdlib.h>
#include <ctype.h>

typedef struct
{
    OptionType option;
    unsigned int startField;
    unsigned int endField;
} FieldOption;

typedef struct FieldsStructure *Fields;

struct FieldsStructure {
    FieldOption *optionsHead;
    unsigned int size;
};

static Fields fields;

BOOL isFieldOption(char *optionString)
{
    return (*optionString == 'k');
}

static BOOL doesExist(void)
{
    return !fields->optionsHead;
}

void FieldOption_Initialize(void)
{
    fields->optionsHead = 0;
    fields->size = 0;
}

void FieldOption_Create(void)
{
    fields->optionsHead = (FieldOption *) malloc(sizeof (FieldOption));
    fields->size = 1;
}

void FieldOption_Extend(void)
{
    fields->optionsHead = (FieldOption *)
        realloc(fields->optionsHead, sizeof (FieldOption) * (fields->size + 1));
    ++fields->size;
}

static FieldOption *currentFieldOption(void)
{
    return fields->optionsHead + fields->size - 1;
}

static char *FieldOption_ParseStartField(char *optionString)
{
    FieldOption *currentOptionp = currentFieldOption();
    do
    {
        currentOptionp->startField = 10 * currentOptionp->startField + *optionString - '0';
    } while (isdigit(*++optionString));

    return optionString;
}

static void FieldOption_ParseEndField(char *optionString)
{
    FieldOption *currentOptionp = currentFieldOption();
    do
    {
        currentOptionp->endField = 10 * currentOptionp->endField + *optionString - '0';
    } while (isdigit(*++optionString));
}

void FieldOption_Parse(char *optionString)
{
    if (doesExist())
        FieldOption_Extend();
    else
        FieldOption_Create();
    optionString = FieldOption_ParseStartField(optionString);
    optionString = SortLines_ParseOption(currentFieldOption()->option, optionString);

    if (!*optionString)
        return;

    if (*optionString != ',')
        return;

    FieldOption_ParseEndField(++optionString);
}
