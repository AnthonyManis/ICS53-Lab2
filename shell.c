#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void promptUser();
int parseCommand(char *line, char *tokens[]);
void quit_command();
void general_command(char *argv[]);

// shows a prompt to the user, gets an input line,
// calls parseCommand, then determines and calls
// the appropriate function for the command
void promptUser() {

    for (;;) {
        char *line = NULL;
        size_t line_size = 0;
        char **argv = NULL;
        int argc = 0;

        printf("prompt>");
        
        int read;
        if ( (read = getline(&line, &line_size, stdin)) > 0 ) {
            if (line[read-1] == '\n') {
                line[read-1] = '\0';
            }
            argc = parseCommand(line, argv);
        }

        if (argc == 0) {
            // no command, do nothing
        }
        else if (!strcmp(argv[0], "quit")) {
            quit_command();

        }
        else {
            general_command(argv);
        }
        free(line);
        int i;
        for (i = 0 ; i < argc ; i++) {
            free(argv[i]);
        }
        free(argv);
    }
}

// parses a line into command & any arguments,
// storing command in (*tokens)[0] and arguments
// each in the following elements
// returns the tokens by reference
// returns the number of tokens or -1 if error
int parseCommand(char *line, char *tokens[]) {
    // tokens in line are separated by spaces, unless
    // enclosed in quotation marks

    // must allocate **tokens array
    int ret = -1;
    return ret;
}

void quit_command() {

}

void general_command(char *argv[]) {

}

int main(int argc, char *argv[]) {
    promptUser();
    return 0;   
}