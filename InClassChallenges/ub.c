#include <stdio.h>

struct animal {
    char *name;
    int leg_count;
};

struct animal *construct_animal(char *name, int leg_count)
{
    struct animal a;

    a.name = name;
    a.leg_count = leg_count;

    return &a;
}

int main(void)
{
    struct animal *a1, *a2;

    a1 = construct_animal("Antelope", 4);
    a2 = construct_animal("Centipede", 100);

    printf("%s %d\n", a1->name, a1->leg_count);
    printf("%s %d\n", a2->name, a2->leg_count);
}

// Questions: When this is run, it returns: 
// Centipede 100
// Centipede 1831662960
// This happens because memory was never allocated to store a1 and a2 so
// a1 Antelope was overwritten by a2 Centipede, then referenced some random data
// that existed in memory for Centipede's leg count.