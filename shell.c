#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SIZE 64

ssize_t readLine(char **bufptr, size_t *n, FILE *fp);

ssize_t readLine(char **bufptr, size_t *n, FILE *fp) {
    ssize_t total;
    int c;
    char *buffer = *bufptr;
    for (total = 0 ; (c = getc(fp)) != EOF && c != '\n' ; total++) {
        // if the buffer pointed to by buffptr isn't big enough
        // to fit the next character then resize it
        if ( total + 1 > *n ) {
            *n = *n + CHUNK_SIZE;
            buffer = realloc(buffer, *n);
        }
        buffer[total] = (char) c;
    }
    bufptr = &buffer;
    return total+1;
}

int main(int argc, char *argv[]) {
    char *buf;
    size_t len = 0;
    ssize_t read;
    read = readLine(&buf, &len, stdin);
    printf("%d characters read, length of buffer now %d,\n%s\n", read, len, buf);
    free(buf);

    return 0;   
}