#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(int argc, char *argv[]) {
    // file descriptors for pipe, 0 is read end, 1 is write end
    int pfd[2];
    // child process ID
    pid_t pid1;

    // create pipe, print error if pipe fails
    if (pipe(pfd) == -1) {
        perror("pipe");
        return 1;
    }

    // fork child process
    pid1 = fork();

    // print error if fork fails
    if (pid1 == -1) {
        perror("fork");
        return 1;
    }

    // if user enters a directory, use that. If not, use current directory
    char *dir;
    if (argc > 1) {
        dir = argv[1];
    } else {
    dir = ".";
    }

    // child process runs wc
    if (pid1 == 0) {
        // close unused Write end of pipe
        close(pfd[1]);
        // redirect pipe Read end to std input
        dup2(pfd[0], 0);
        // close Read end after dup'ing
        close(pfd[0]);
        // run wc, counting lines from std input
        execlp("wc", "wc", "-l", NULL);
        // print error if execlp fails
        perror("execlp wc");
        exit(1);

    // parent process runs ls -1a
    } else {
        // close unused Read end of pipe
        close(pfd[0]);
        // redirect pipe Write end to std output
        dup2(pfd[1], 1);
        // close Write end after dup'ing
        close(pfd[1]);
        // run ls -1a
        execlp("ls", "ls", "-1a", dir, NULL);
        // print error if execlp fails
        perror("execlp ls");
        exit(1);
    }
    
    // parent waits for child to be done
    wait(NULL);

    return 0;

}