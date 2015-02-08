#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 10

char *concatenate(char* a, char* b) {
    // Get length of strings.
    int len_a = strlen(a);
    int len_b = strlen(b);
    int length = len_a + len_b + 1;

    int i = 0;

    char* c = (char*) malloc(sizeof(char) * length + 1);

    for (i = 0; i < len_a; i++) {
        c[i] = a[i];
    }

    for (i = 0; i < len_b; i++) {
        c[len_a + i] = b[i];
    }

    c[length - 1] = '\0';

    return c;
}

int main(int argc, char** argv) {
    if (argc < 4) {
        printf("Usage: hw1_leaky <count> <firstword> <secondword>\n");
        exit(1);
    }

    char* middle = "cruel";
    char number[MAXCHAR];
    int i = 0;

    for (i = 0; i < atoi(argv[1]); i++) {
        sprintf(number, "%d", i);

        char* line = concatenate(
                concatenate(argv[2], number),
                concatenate(middle,
                    concatenate(number, argv[3])));
        if (i < 0)
            free(middle);

        printf("%s\n", line);
        middle = line;
    }

    free(middle);
}
