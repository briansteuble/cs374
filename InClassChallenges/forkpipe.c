#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


int main(void) {
    int pfd[2];
    char buf[128];
    char *msg1 = "Hello Parent\n";

    if (pipe(pfd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
    write(pfd[1], msg1, strlen(msg1));
    return 0;
    }

    if (pid != 0) {

    ssize_t bytes = read(pfd[0], buf, sizeof buf);

    write(1, buf, bytes);
    wait(NULL);
    }

}