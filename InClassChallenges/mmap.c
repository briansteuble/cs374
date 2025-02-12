#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

const int SIZE=1024;  // bytes

struct bicycle {
    int wheel_count;
    char name[32];
};

int main(void)
{
    // Allocate some space from the OS
    void *heap = mmap(NULL, SIZE, PROT_READ|PROT_WRITE,
                  MAP_ANON|MAP_PRIVATE, -1, 0);

    // Challenge 1:
    //
    // Treat heap as an array of chars
    // Store a string there with strcpy() and print it
    char *string = (char *)heap;
    strcpy(string, "string");
    printf("%s\n", string);

    // Challenge 2:
    //
    // Treat heap as an array of ints
    // Use a loop to store the values 0, 10, 20, 30, 40 in it
    // Use a loop to retrieve the value and print them
    int *array = (int *)heap;
    for (int i = 0; i <= 4; i++) {
        array[i] = i*10;
    }
    for (int i = 0; i <= 4; i++) {
        printf("%d\n", array[i]);
    }



    // Challenge 3:
    //
    // Treat heap as an array of struct bicycles
    // Store 3 bicycles
    // Print out the bicycle data in a loop

    struct bicycle *bike_array = (struct bicycle *)heap;


    strcpy(bike_array[0].name, "normalbike");
    bike_array[0].wheel_count = 2;
    strcpy(bike_array[1].name, "quadbike");
    bike_array[1].wheel_count = 4;
    strcpy(bike_array[2].name, "trikebike");
    bike_array[2].wheel_count = 3;

    for (int i = 0; i < 3; i++) {
        printf("%s has %d wheels\n", bike_array[i].name, bike_array[i].wheel_count);
    }



    // Challenge 4:
    //
    // If you used pointer notation, redo challenges 1-3 with array
    // notation, and vice versa.

    // Part 2 with pointers:
    int *array2 = heap;
        for (int i = 0; i <= 4; i++) {
        *(array2 + i) = i*10;
    }
    for (int i = 0; i <= 4; i++) {
        printf("%d\n", *(array2 + i));
    }

    // Part 3 with pointers:
    struct bicycle *bikes = heap;
        (bikes+0)->wheel_count = 2;
        strcpy((bikes+0)->name, "normalbike");
        (bikes+1)->wheel_count = 4;
        strcpy((bikes+1)->name, "quadbike");
        (bikes+2)->wheel_count = 3;
        strcpy((bikes+2)->name, "trikebike");

    for (int i = 0; i < 3; i++) {
        printf("%s has %d wheels\n", (bikes+i)->name, (bikes+i)->wheel_count);
    }


    // Challenge 5:
    //
    // Make the first 32 bytes of the heap a string (array of chars),
    // and follow that directly with an array of ints.
    //
    // Store a short string in the string area of the heap
    // Use a loop to store the values 0, 10, 20, 30, 40 in the int array
    // Use a loop to retrieve the value and print them
    // Print the string
        strcpy(heap, "hello string");

        int *ip = (int *)((char *)heap + 32);

        for (int i = 0; i <= 4; i++)
            ip[i] = i * 10;

        for (int i = 0; i <= 4; i++)
            printf("%d\n", ip[i]);

        puts(heap);

    // Free it up
    munmap(heap, SIZE);
}