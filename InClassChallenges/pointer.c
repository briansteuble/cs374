#include <stdio.h>

// Do not change the return type from `void`!
void increment(int *x)
{
    (*x)++;
}

int main(void)
{
    int a = 12;

    int *p = &a;
    
    increment(p);

    // This should print 13, but it only prints 12!
    printf("%d\n", a);
}