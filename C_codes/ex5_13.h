enum {ERROR = -1, SUCCESS = 0};

int readLineWrappedN(void);
void writeLineWrappedN(void);
/* heap representations */
char *allocWrapped(int, char *);
char *firstPointer(void);
char isLastPointer(char *);
void installWrapped(char *, char *, int);
/* queue representation */
void setLastN(int);
void freeLastN(void);
void insertLast(char *, int);
void destroyIfHeld(char *);
char existDestroyed(void);
void inspectLastN(void);
