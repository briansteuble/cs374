#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void) {


    int fd;

    if ((fd = open("output.txt", O_CREAT|O_TRUNC|O_WRONLY, 0744)) == -1)  {
    perror("open");
    return 1;
} 
    int old_stdout = dup(1);

    dup2(fd ,1);

    printf("Hello, world\nThis is a test!\n");

    fflush(stdout);

    close(fd);
    dup2(old_stdout, 1);

    printf("All done!\n");

    return 0;

}