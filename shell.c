#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void promptUser();
int parseCommand(char *line, size_t *n, char *tokens[]);
int get_token(char **token, size_t *n, char *delims, char* str);
void quit_command();
void general_command(char *argv[]);

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
        
        int read;
        if ( (read = getline(&line, &line_size, stdin)) > 0 ) {
            if (line[read-1] == '\n') {
                line[read-1] = '\0';
            }
        }
        int argc = parseCommand(line, &n, argv);
        free(line);

        // as long as the line wasn't blank
        if (argc > 0) {
            if (!strcmp(argv[0], "quit")) {
                quit_command();

            }
            else {
                general_command(argv);
            }
        }
        if (argc != -1){
            int i;
            for (i = 0 ; i < n ; i++) {
                free(argv[i]);
            }
        }
    }
}

// parses a line into command & any arguments,
// storing command in (*tokens)[0] and arguments
// each in the following elements
// n is the size of the final array (for caller to free())
// returns the tokens by reference
// returns the number of tokens or -1 if allocation error
int parseCommand(char *line, size_t *n, char *tokens[]) {
    // line pointer can not be null
    if (!line)
        return -1;

    // allocate initial space to tokens array
    if (!tokens) {
        *n = 2;
        tokens = malloc(*n * sizeof(char *));
        if (!tokens)
            return -1; // failed to allocate
    }

    // tokens in line are separated by whitespace, unless
    // enclosed in quotation marks
    char *tp = NULL; // token pointer
    size_t token_size = 0;
    get_token(&tp, &token_size, " \t\n", line);
    int counter = 0;
    while (tp)
    {
        // reallocate tokens array if necessary
        if (counter >= *n) {
            *n *= 2;
            tokens = realloc(tokens, *n * sizeof(char*));
            if (!tokens)
                return -1; // failed to reallocate
        }
        // always allocate for each token
        tokens[counter] = malloc(strlen(tp) + 1);
        if (!tokens[counter])
            return -1; // failed to allocate
        strcpy(tokens[counter], tp);
        ++counter;

        free(tp);
        token_size = 0;
        get_token(&tp, &token_size, " \t\n", line);
    }
    if (tp)
        free(tp);

    return counter;
}

// gets a token, seperated by any number of delims
// returns number of characters read not including '\0'
// token is stored with terminating '\0' into token
// dynamically allocates token as necessary, caller must free() token
int get_token(char **token, size_t *n, char *delims, char* str) {

}

void quit_command() {

}

void general_command(char *argv[]) {

}

int main(int argc, char *argv[]) {

	promptUser();
    return 0;   
}
