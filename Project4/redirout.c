#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    // print error if lack of arguments
    if (argc < 3) {
        perror("Not enough arguments, must be at least 3");
        return 1;
    }

    // extract output file
    char *outfilename = argv[1];
    // extract command, arguments
    char **command = &argv[2];

    // open the file for writing
    int fd = open(outfilename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    // print error if open fails
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // fork a new process
    pid_t pid = fork();
    // print error if fork fails
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    // child process
    if (pid == 0) { 
        // redirect stdout to file
        dup2(fd, STDOUT_FILENO); 
        close(fd); 
        // execute command
        execvp(command[0], command); 
        // print error if exec fails
        perror("execvp"); 
        exit(1);
    }

    // close file descriptor 
    close(fd); 
    // parent waits for child to be done
    wait(NULL); 

return 0;
}