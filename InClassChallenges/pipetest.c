#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int main(void) {
    int pfd[2];
    char buf[128];

    if (pipe(pfd) == -1) {
        perror("pipe");
        return 1;
    }

    ssize_t count = write(pfd[1], "Hello\n", 6);

    if (count == -1) {
        perror("write");
        return 2;
    }

    count = read(pfd[0], buf, 128);

    if (count == -1) {
        perror("read");
        return 3;
    }

    write(1, buf, count);
    

}