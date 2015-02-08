#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 10

void* mymalloc(int size) {
    void* ptr = malloc(size);
    fprintf(stderr, "malloc: %p\n", ptr);
    return ptr;
}

void myfree(void* ptr) {
    fprintf(stderr, "free: %p\n", ptr);
    free(ptr);
}

char *concatenate(char* a, char* b) {
    // Get length of strings.
    int len_a = strlen(a);
    int len_b = strlen(b);
    int length = len_a + len_b; // Extra space for null terminator.

    int i = 0;

    char* c = (char*) mymalloc(sizeof(char) * length + 1);

    for (i = 0; i < len_a; i++) {
        c[i] = a[i];
    }

    for (i = 0; i < len_b; i++) {
        c[len_a + i] = b[i];
    }

    c[length] = '\0'; // Append null terminator to string.

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

        // Begin leaky
        char* head = concatenate(argv[2], number);
        char* tail = concatenate(number, argv[3]);
        char* body = concatenate(middle, tail);
        char* line = concatenate(head, body);

        myfree(head);
        myfree(tail);
        myfree(body);

        if (i > 0)
            myfree(middle);
 
        // End leaky

        printf("%s\n", line);
        middle = line;
    }

    myfree(middle);
}
