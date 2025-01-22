#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    (void)argc;

    char *token;
    char line[1024];

    fgets(line, sizeof line, stdin);

    size_t length = strlen(line);
    if (length > 0 && line[length - 1] == '\n') {
        line[length -1] = '\0';
    }

    token = strtok(line, " ");
    while (token != NULL) {
        puts(token);
        token = strtok(NULL, " ");
    }

}

// Questions (Answers): I used strlen find the length of the string, assumed the \n
// character would be at position length-1, then replaced it with \0. 
// You could alternatively use strcspn() to find the position of the first \n
// and replace it with \0.