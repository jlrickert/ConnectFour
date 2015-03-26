#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "helper.h"


void
clear_lines(unsigned int nLines)
{
#ifdef __unix__
    /* printf("%c[2K\b\b", 27); */
    printf("\033[2K");
    for (int i = 0; i < nLines; i++) {
        printf("\033[A");
        printf("\033[2K");
    }
    /* printf("%c[2K\b\b", 27); */
#elif __WIN32
    // need a compatible implimentation
#endif
}

int
get_str(char** buffer)
{
    unsigned int bCapacity = 32;
    unsigned int bLength = 0;
    int c;

    *buffer = malloc(sizeof(char) * bCapacity);
    if (*buffer == NULL) return -1;

    while ((c = fgetc(stdin)) != '\n' && c != EOF) {
        if (bLength + 1 > bCapacity) {
            if (bCapacity <= (UINT_MAX / 2)) {
                bCapacity *= 2;
            } else {
                free(buffer);
                return -1;
            }
            char* tmp = realloc(*buffer, bCapacity * sizeof(char));
            if (buffer == NULL) {
                free(buffer);
                return -1;
            }
            buffer[0] = tmp;
        }

        buffer[0][bLength++] = c;
    }
    buffer[0][bLength++] = '\0';

    return bLength;
}

int
get_int()
{
    char* line;
    int len = get_str(&line);
    clear_lines(0);

    loop {
        int n; char c;
        if (sscanf(line, " %i %c", &n, &c) == 1) {
            free(line);
            return n;
        } else {
            clear_lines(0);
            printf("Invalid! Please renter: ");
            len = get_str(&line);
            clear_lines(1);
        }
    }
}

