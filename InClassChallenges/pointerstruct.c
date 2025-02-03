#include <stdio.h>

struct animal {
    char *name;
    int leg_count;
};

void increment_leg_count(struct animal *p)
{
    // TODO Increment leg count of `p`
    p->leg_count++;
}

int main(void)
{
    struct animal a = {.name="Antelope", .leg_count=3};

    // TODO Call increment_leg_count on `a`
    increment_leg_count(&a);

    printf("%d\n", a.leg_count); // Should print 4
}