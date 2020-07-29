#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int request_res();
int release_res();
int safety_algorithm();
int readFile(char* fileName);

int main(int argc, char* argv[]) {
    int resource_count = argc - 1;
    int customer_count = 5;

    int available[resource_count];
    int maximum[customer_count][resource_count];
    // int allocation[customer_count][resource_count];
    // int need[customer_count][resource_count];

    printf("Number of Customers: %d\n", customer_count);

    // Initialize Data
    for (int x = 0; x < resource_count; x++) {
        int num = strtol(argv[x + 1], NULL, 10);
        available[x] = num;
        //printf("%d", num);
    }

    printf("Maximum resources from file:\n");
    for (int x = 0; x < customer_count; x++) {
        for (int i = 0; i < resource_count; i++) {
            max[x][i] = available[i];
            printf("%d", max[x][i]);
            if (i + 1 < resource_count) printf(",");
        }
        printf("\n");
    }

    // for (int x = 0; x < customer_count; x++) {
    //     for (int i = 0; i < resource_count; i++) {
    //         allocation[x][i] = 0;
    //     }
    // }
}

int readFile(char* fileName) {
    FILE* in = fopen(fileName, "r");
    if (!in) {
        printf("Error in opening input file...exiting with error code -1\n");
        return -1;
    }
    const char *delim = ",\n\t ";
    char line[20];
    char* token;
    int i, n, j; 
    i = 0;
    // Read file line by line
    while (fgets(line, sizeof(line), in)) {
        j = 0;
        // Initalize line tokens 
        token = strtok(line, delim);
        // While not empty 
        printf("\n");
        while (token != NULL) {
            n = atoi(token);
            maximum[i][j] = n;
            printf(" %d", maximum[i][j]);
            j++;
            token = strtok(NULL, delim);
        }
        i++;
    }
    return 0;
}