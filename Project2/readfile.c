#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 2048

int main(int argc, char *argv[]) {
    
    // Capture an error if a filename isnt given
    if (argc < 2) {
        perror("No file specified");
        return 1;
    }

    const char *filename = argv[1];

    // Open the file as read-only, get file descriptor
    int fd = open(filename, O_RDONLY);

    // Check for invalid file descriptor
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    // Set the buffer to our defined buffer size of 2048 bytes
    char buffer[BUFFER_SIZE];
    // Store number of bytes read
    ssize_t bytes_read;

    // Read and write in chunks of 2048 bytes
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buffer, bytes_read) == -1) {
            perror("Error writing to standard output");
            close(fd);
            return 1;
        }
    }
    // Check for a reading error
    if (bytes_read == -1) {
        perror("Error reading from file");
        close(fd);
        return 1;
    }

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("Error closing file");
        return 1;
    }

    return 0;
}