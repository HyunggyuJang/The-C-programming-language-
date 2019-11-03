#include <stdio.h>






int main() {
long ns, nt, nl;
int c;

ns = 0;
nt = 0;
nl = 0;

while ((c = getchar ()) != EOF) {
    if (c == ' ')
        ++ns;
    if (c == '\t')
        ++nt;
    if (c == '\n')
        ++nl;
}
printf("The number of blanks, tabs, lines are %ld, %ld, %ld, respectively\n", ns, nt, nl);
return 0;
}
