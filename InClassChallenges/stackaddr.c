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