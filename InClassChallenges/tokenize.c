#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    (void)argc;

    char *string = argv[1];
    char *token = strtok(string, " ");

    if (token != NULL) do
        puts(token);  // do something with the token
    while ((token = strtok(NULL, " ")) != NULL);

}

// Questions (Answers): We pass a pointer the first time to tell strtok where
// it should start tokenizing the string. Using NULL on subsequent calls tells
// strtok to hold its place and process the next chunk of the string. Passing the
// pointer on every call would just return the first arg of the string.