#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void request_res(int, int, int, int);
void release_res(int, int, int, int);
int safety_algorithm();
int readFile(char* fileName);  //, int* maximum[]);

int main(int argc, char* argv[]) {
    int resource_count = argc - 1;
    int customer_count = 5;

    // User input
    // char cmd[3];
    // int cmd_res[4];
    // char req[] = "RQ";
    // char rel[] = "RL";

    int available[resource_count];
    int maximum[customer_count][resource_count];
    readFile("sample4_in.txt");  //, maximum);
    printf("\n\n%d\n", maximum[0][1]);
    // int maximum[][4] = {
    //     {6, 4, 7, 3}, {4, 2, 3, 2}, {2, 5, 3, 3}, {6, 3, 3, 2}, {5, 6, 7, 5}};
    // int allocation[customer_count][resource_count];
    // int need[customer_count][resource_count];

    printf("Number of Customers: %d\n", customer_count);
    printf("Currently Available Resources: ");
    // Initialize Data
    for (int x = 0; x < resource_count; x++) {
        int num = strtol(argv[x + 1], NULL, 10);
        available[x] = num;
        printf(" %d", available[x]);
    }

    // TODO: Actually read input data
    // printf("\nMaximum resources from file:\n");
    // for (int x = 0; x < customer_count; x++) {
    //     for (int i = 0; i < resource_count; i++) {
    //         printf("%d", maximum[x][i]);
    //         if (i + 1 < resource_count) printf(",");
    //     }
    //     printf("\n");
    // }

    // for (int x = 0; x < customer_count; x++) {
    //     for (int i = 0; i < resource_count; i++) {
    //         allocation[x][i] = 0;
    //     }
    // }
    /*
    while (1) {
        printf("Enter Command: ");
        scanf("%s %d %d %d %d", cmd, &cmd_res[0], &cmd_res[1], &cmd_res[2], &cmd_res[3]);

        printf("Entered Name: %s\n", cmd);
        // printf("%d\n", cmd_res[2]);

        if (strcmp(cmd, req) == 0) {
            request_res((int)&cmd_res[0], (int)&cmd_res[1], (int)&cmd_res[2], (int)&cmd_res[3]);
        } else if (strcmp(cmd, rel) == 0) {
            request_res(&cmd_res[0], &cmd_res[1], &cmd_res[2], &cmd_res[3]);
        } else {
            printf("ya dun fucked up now\n");
        }
    }
    */
}

int readFile(char* fileName) {  //, int* maximum[]) {
    FILE* in = fopen(fileName, "r");
    if (!in) {
        printf("Error in opening input file...exiting with error code -1\n");
        return -1;
    }

    int i, j, n;
    const char delim[2] = ",";
    char* token;

    char line[10];
    i = 0;
    while (fgets(line, sizeof(line), in)) {
        j = 1;
        //printf("%s", line);
        token = strtok(line, delim);
        while (token != NULL) {
            //printf(" %s", token);
            n = atoi(token);
            maximum[i][j] = n;
            j++;
            printf("%d ", maximum[i][j]);
            token = strtok(NULL, delim);
        }
        maximum[i][0] = j;
        i++;
    }
    return 0;
}