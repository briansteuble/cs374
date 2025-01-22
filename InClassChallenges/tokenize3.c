#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    (void)argc;

    char *token;
    char line[1024];
    char *tokens[128] = {0};
    int token_count = 0;

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

    for(int i = 0; tokens[i] != NULL; i++)
        printf("%d: %s\n", i, tokens[i]);

}

// Questions (Answers): Without initializing the array to all NULL pointers,
// it would contain garbage values and the loop would keep running past our tokens, 
// attempting to dereference the garbage, leading to who knows what.