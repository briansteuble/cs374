#include <stdio.h>

int main() {

    // Declare variables
    int x = 12;
    float y = 3.14;
    char *s = "Hello, world!";

    // Print x, y, and s
    printf("x is %d, y is %f\n", x, y);
    printf("%s\n", s);

    // Declare z
    int z = 0;

    // Loop to print 5 * z while z < 5
    while (z < 5) {
        printf("%d x 5 = %d,\n", z, z*5);
        z++;
    }

    return 0;

}

