#include <stdio.h>

void loop(int *n) {
    if (*n < 1) return;

    printf("Value: %d, Address: %p\n", *n, (void*)n);

    int next = *n -1;
    loop(&next);
}

int main() {
    int start = 9;
    loop(&start);
    return 0;
}

//Question: What do you observe about the address of the variable on the stack? Is it increasing or decreasing from call to call? Why?
// The address is decreasing because the stack grows downward.