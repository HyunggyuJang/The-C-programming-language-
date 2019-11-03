#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

float fahr2cels(float fahr);
/* test temperature conversion function */
main () {
    float fahr;
    for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
        printf("%3.0f %6.1f\n", fahr, fahr2cels(fahr));
    return 0;
}
/* temperature conversion function from fahrenheit to celsius*/
float fahr2cels(float fahr) {
    return (5.0/9.0) * (fahr - 32.0);
}
