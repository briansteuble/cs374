#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 2048

// Function to read from a file descriptor
void process_fd(int fd) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Write to standard output until read returns 0 (end of file) 
    // Capture writing errors
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buffer, bytes_read) == -1) {
            perror("Error writing to standard output");
            exit(1);
        }
    }

    // Capture read errors
    if (bytes_read == -1) {
        perror("Error reading from file");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // No files specified, use standard input
        process_fd(STDIN_FILENO);
    } else {
        // Loop through the files specified in argv
        for (int i = 1; i < argc; i++) {
            int fd = open(argv[i], O_RDONLY);
            if (fd == -1) {
                perror("Error opening file");
                continue; // Skip to the next file
            }

            process_fd(fd);

            // Capture file closing errors
            if (close(fd) == -1) {
                perror("Error closing file");
                exit(1);
            }
        }
    }

    return 0;
}