#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// Run external command function
void run_command(char *args[]) {

    // Fork child process
    pid_t pid = fork();

    if (pid == 0) { 
        // Replace child program with requested program, check for execvp failure
        if (execvp(args[0], args) == -1) {
            perror("mush");
            // exit upon failure
            exit(1);
        }

    // Parent process waits for child to complete
    } else if (pid > 0) { 
        wait(NULL);

    // Check for fork failure
    } else {
        perror("mush: fork failed");
    }
}

// Main function
int main() {
    char line[2048];
    char *tokens[128];
    char *token;
    int running_shell = 1;

    while (running_shell == 1) {

        // Print mush shell prompt to screen
        printf("mush> ");
        fflush(stdout);

        // Read a line of input
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\n");
            break;
        }

        // Replace newline character with \0
        size_t length = strlen(line);
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }

        // Re-loop to print another prompt if user presses enter on an empty line
        if (strlen(line) == 0) {
            continue;
        }

        // Tokenize input
        int token_count = 0;
        token = strtok(line, " ");
        while (token != NULL && token_count < 128) {
            tokens[token_count++] = token;
            token = strtok(NULL, " ");
        }

        // Terminate array with NULL
        tokens[token_count] = NULL;

        // Internal cd command logic
        // If user enters cd...
        if (strcmp(tokens[0], "cd") == 0) {

            // Flag error for no cd argument
            if (token_count < 2) {
                printf("mush: cd: missing argument\n");

                // Flag error if chdir returns -1
            } else {
                if (chdir(tokens[1]) == -1) {
                    perror("mush: cd");
                }
            }
            continue;
        }

        // Internal exit command - exit shell
        if (strcmp(tokens[0], "exit") == 0) {
            printf("Adios amigo!\n");
            running_shell = 0;
            continue;
        }

        // Run external command
        run_command(tokens);
    }
    
    return 0;
}