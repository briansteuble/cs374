#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

void loop(int *n) {
    if (*n < 1) return;
    
    int next = *n - 1;
    loop(&next);
}

int main() {
    int start = 9;
    loop(&start);
    
    for (int i = 1; i <= 9; i++) {
        void *heap = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                          MAP_ANON | MAP_PRIVATE, -1, 0);
        printf("Loop Index: %d, Address: %p\n", i, heap);
    }
    
    return 0;
}

// Question: What do you observe about the address of the mmap()d region? Is it increasing or decreasing from call to call? Why?
// The addresses are increasing because the heap grows upward.
