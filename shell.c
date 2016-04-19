#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SIZE 64

ssize_t readLine(char **bufptr, size_t *n, FILE *fp);

// reads a line into buffer, reallocating memory if necessary
// buffer will be terminated by '\0'
// allocated size of buffer array after operation is n
// returns the number of characters read, not including '\n'
// returns -1 if stream error or no bytes read
// caller must free the buffer after use
ssize_t readLine(char **bufptr, size_t *n, FILE *fp) {
    char *position;
    size_t available;

    if (!*n) {
        *n = CHUNK_SIZE;
    }

    if (!*bufptr) {
        *bufptr = malloc(*n);
        if (!*bufptr) {
            return -1;
        }
    }
    position = *bufptr;
    available = *n;
    for (;;) {
        int c = getc(fp);
        if ((*bufptr + *n) != (position + available)) {
            return -1;
        }
        // resize the buffer if it isn't big enough
        // to store character and null terminator
        if (available < 2) {
            if (*n > CHUNK_SIZE) {
                *n *= 2;
            }
            else {
                *n += CHUNK_SIZE;
            }
            available = *n + (*bufptr - position);
            *bufptr = realloc(*bufptr, *n);
            if (!*bufptr) {
                return -1;
            }
            position = *bufptr + (*n - available);
        }

        if (c == EOF) {
            if (position == *bufptr) {
                return -1;
            }
            else {
                break;
            }
        }

        // terminator
        if (c =='\n') {
            break;
        }

        *position++ = c;
        available--;


    }
    *position = '\0';
    return (position - *bufptr);
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