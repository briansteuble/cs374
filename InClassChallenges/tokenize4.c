#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    (void)argc;

    char *token;
    char line[1024];
    char *tokens[128] = {0};
    int token_count = 0;

    printf("prompt> ");
    fflush(stdout);

    fgets(line, sizeof line, stdin);

    size_t length = strlen(line);
    if (length > 0 && line[length - 1] == '\n') {
        line[length -1] = '\0';
    }

    token = strtok(line, " ");
    while (token != NULL && token_count < 128) {
        tokens[token_count++] = token;
        token = strtok(NULL, " ");
    }

    execvp(tokens[0], tokens);

}

// Questions (Answers): Entering "jksdfg" or some other nonsense will cause execvp()
// to fail since it is expecting a valid program to start running. You could implement
// error handling by checking if execvp() returns -1 (failure) and adding a print
// statement saying something like: "Error: invalid command"