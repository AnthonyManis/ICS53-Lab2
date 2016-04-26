#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



void promptUser();
int parseCommand(char *line, size_t *n, char ***tokens);
void quit_command();
void general_command(char **argv, int num_of_elements, bool present);

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
                break;
            }
            else {
                general_command(argv, 0, true);
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

    char *in_quotes_delims = "\n";
    char *out_quotes_delims = " \t\n";
    char *delims = out_quotes_delims;
    char *token_begin = NULL;
    char *token_end = line;
    size_t token_size = 0;
    size_t count = 0;
    bool in_quotes = false;

    while (*token_end) {
        if (count >= *n) {
            *n = *n * 2;
            *tokens = realloc(*tokens, *n * sizeof(char*));
            if (!*tokens)
                return -1;
        }
        // quotes surround a single token that has spaces in it
        // changes the delims string if inside quotes
        if (strchr("\"", *token_end)) {
            if (!in_quotes) {
                in_quotes = true;
                delims = in_quotes_delims;
            }
            else {
                in_quotes = false;
                delims = out_quotes_delims;
            }
        }
        if (!strchr(delims, *token_end)) {
            // ignore leading whitespace
            if (!token_begin) {
                token_begin = token_end;
            }
            token_size++;
            token_end++;
        }
        else { // new delimiter found, store the current token
            if (token_begin) {
                (*tokens)[count] = malloc(token_size+1);
                if (!(*tokens)[count])
                    return -1;
                strncpy((*tokens)[count], token_begin, token_size);
                (*tokens)[count][token_size] = '\0';
                token_size = 0;
                count++;
            }
            // advance to next token
            while(*token_end && strchr(delims, *token_end)){
                token_end++;
            }
            token_begin = token_end;
        }
    }
    return count;
}

void general_command(char **argv, int num_of_elements, bool present) {

}

int main(int argc, char *argv[]) {

	promptUser();
    return 0;
}
