#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void promptUser();
int parseCommand(char *line, size_t *n, char ***tokens);
void quit_command();
void general_command(char **argv);

// shows a prompt to the user, gets an input line,
// calls parseCommand, then determines and calls
// the appropriate function for the command
void promptUser() {

    for (;;) {
        char *line = NULL;
        char **argv = NULL;
        size_t line_size = 0;
        size_t n = 0;

        printf("prompt>");
        
        getline(&line, &line_size, stdin);
        int argc = parseCommand(line, &n, &argv);
        free(line);
        printf("%d tokens parsed\n", argc);
        if (argc > 0) {
            int i;
            for (i = 0 ; i < argc ; i++) {
                printf("argv %d: %s\n", i, argv[i]);
            }
            if (!strcmp(argv[0], "quit")) {
                quit_command();
                break;
            }
            else {
                general_command(argv);
            }
        }
        if (argc != -1) {
            int i;
            for (i = 0 ; i < argc ; i++) {
                free(argv[i]);
            }
        }
        free(argv);
    }
}

// parses a line into command & any arguments,
// storing command and arguments as tokens in the (*tokens) array
// n is the size of the final array
// returns the number of tokens allocated or -1 if allocation error
int parseCommand(char *line, size_t *n, char ***tokens) {
    if (!line)
        return -1;
    if (!*tokens) {
        *n = 2;
        *tokens = malloc(*n * sizeof(char*));
        if (!*tokens)
            return -1;
    }

    char *delims = " \t\n";
    char *tp = line;
    char *next_token = line;
    size_t token_size = 0;
    size_t count = 0;

    while (*next_token) {
        if (count >= *n) {
            *n = *n * 2;
            *tokens = realloc(*tokens, *n * sizeof(char*));
            if (!*tokens)
                return -1;
        }
        if (!strchr(delims, *next_token)) {
            token_size++;
            next_token++;
        }
        else {
            (*tokens)[count] = malloc(token_size+1);
            if (!(*tokens)[count])
                return -1;
            strncpy((*tokens)[count], tp, token_size);
            (*tokens)[count][token_size] = '\0';
            token_size = 0;
            count++;
            while(*next_token && strchr(delims, *next_token)){
                next_token++;
            }
            tp = next_token;
        }
    }
    return count;
}

void quit_command() {

}

void general_command(char **argv) {

}

int main(int argc, char *argv[]) {

	promptUser();
    return 0;   
}
