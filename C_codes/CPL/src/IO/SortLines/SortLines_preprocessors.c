#include "SortLines_internal.h"

/* toLowers ADT */
void toLowers(char *destination, char *source)
{
    while ((*destination++ = tolower(*source++)))
        ;
}

/* toDirectoryCharsADT */
void toDirectoryChars(char *destination, char *source)
{
    for (; *source; ++source)
        if (isalnum(*source) || *source == ' ')
            *destination++ = *source;
    *destination = '\0';
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

void (*chooseFieldFromRange(int startingField, int endingField))(char *, char *)
{
    startField = startingField;
    endField = endingField;
    return chooseField;
}
