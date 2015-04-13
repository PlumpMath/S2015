#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_VALUES 16

void init_array(int *values) {
    int i, index, temp;

    /* Initialize array with values. */
    for (i = 0; i < NUM_VALUES; i++)
    {
        values[i] = i;
    }

    /* Shuffle values in array. */
    /* Generate random seed. */
    srand((unsigned)time(NULL));

    for (i = 0; i < NUM_VALUES; i++)
    {
        /* Get random index */
        index = rand() % NUM_VALUES;

        /* Swap values */
        temp = values[i];
        values[i] = values[index];
        values[index] = temp;
    }
}

int forkSearch(int* data, int searchValue, int start, int end)
{
    // Data is a single element.
    if (start == end)
    {
        if (*(data + start) == searchValue)
        {
            return start;
        }
        exit(0);
    } 
    else
    {
        pid_t child = fork();
        if (child == 0) // Child process
        {
            return forkSearch(data, searchValue, start, (start + end) / 2);
        }
        else // Parent process
        {
            return forkSearch(data, searchValue, (start + end) / 2 + 1, end);
        }
    }

    return -1;
}

int main(int argc, char* argv[])
{
    int *data = (int*)malloc(sizeof(int) * NUM_VALUES);

    /* Check arguments. */
    if (argc != 2) 
    {
        printf("Usage: ./hw2_search <search_value>\n");
        return 1;
    }

    int searchValue = atoi(argv[1]);
    if (searchValue < 0 || searchValue > 15)
    {
        fprintf(stderr, "ERROR: Invalid search value %d\n", searchValue);
        return 1;
    }

    init_array(data);
    
    printf("Search value %d found at index %d in data.\n",
            searchValue, forkSearch(data, searchValue, 0, NUM_VALUES - 1)); 

    free(data);

    return 0; 
}

