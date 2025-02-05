#include <stdio.h>
#include <stdlib.h>

struct animal {
    char *name;
    int leg_count;
};

int main(void)
{
    struct animal *a;

    a = malloc(sizeof(struct animal));

    if (a == NULL) {
        perror("malloc failed");
        return EXIT_FAILURE;
    }

    a->name = "Antelope";
    a->leg_count = 4;
    printf("%s %d\n", a->name, a->leg_count);

    free(a);
}