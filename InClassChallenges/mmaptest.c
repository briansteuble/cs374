#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

struct animal {
    char *name;
    int leg_count;
};

int main(void)
{
    struct animal *a;

    a = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);

    if (a == MAP_FAILED) {
        perror("mmap failed");
        return EXIT_FAILURE;
    }

    a->name = "Antelope";
    a->leg_count = 4;
    printf("%s %d\n", a->name, a->leg_count);

    munmap(a, 4096);
}

// Quesitons: Mmap allocates memory in multiples of pagesize, one page being 4096 bytes.
// 4096 bytes is more than we need but the unused space isnt harmful, it'll all be freed
// when we call munmap anyway.
// If we try to allocate less than 4096 bytes, mmap will still allocate the minimum pagesize
// of 4096 bytes, and "any extension beyond the end of the mapped object will be zero-filled".