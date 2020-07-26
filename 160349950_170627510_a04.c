#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int request_res(int cmd_res[], int res_count, int proc_count, int available[], int allocation[][res_count], int maximum[][4]);
int release_res(int cmd_res[]);
void run();
void output_data();
int safety_algorithm(int res_count, int proc_count, int available[], int allocation[][res_count], int need[res_count], int maximum[][4]);
int readFile(char* fileName);  //, int* maximum[]);

int main(int argc, char* argv[]) {
    int resource_count = argc - 2;
    printf("Resource count is %d\n", resource_count);
    int customer_count = 5;

    // User input
    char cmd[3];
    int cmd_res[4];
    char req[] = "RQ";
    char rel[] = "RL";
    char execute[] = "Run";
    char star[] = "*";

    int available[resource_count];
    // int maximum[customer_count][resource_count];
    // readFile("sample4_in.txt");  //, maximum);
    // printf("\n\n%d\n", maximum[0][1]);
    int maximum[][4] = {
        {6, 4, 7, 3}, {4, 2, 3, 2}, {2, 5, 3, 3}, {6, 3, 3, 2}, {5, 6, 7, 5}};
    int allocation[customer_count][resource_count];
    int need[customer_count][resource_count];

    printf("Number of Customers: %d\n", customer_count);
    printf("Currently Available Resources: ");

    // Initialize Data from command line
    for (int x = 0; x < resource_count; x++) {
        int num = strtol(argv[x + 1], NULL, 10);
        available[x] = num;
        printf(" %d", available[x]);
    }

    // TODO: Actually read input data
    printf("\nMaximum resources from file:\n");
    for (int x = 0; x < customer_count; x++) {
        for (int i = 0; i < resource_count; i++) {
            printf("%d", maximum[x][i]);
            if (i + 1 < resource_count) printf(",");
        }
        printf("\n");
    }

    // Initialize allocation/need arrays
    for (int x = 0; x < customer_count; x++) {
        for (int i = 0; i < resource_count; i++) {
            allocation[x][i] = 0;
            need[x][i] = maximum[x][i];
            // TODO: Remove these print statements eventually
            printf("%d", allocation[x][i]);
            printf("%d", need[x][i]);
        }
    }
    printf(" <-- Ignore this number\n");

    // Main function loop
    while (1) {
        printf("Enter Command: ");
        scanf("%s %d %d %d %d", cmd, &cmd_res[0], &cmd_res[1], &cmd_res[2], &cmd_res[3]);

        //printf("Entered Name: %s\n", cmd);
        //printf("%d\n", cmd_res[2]);

        if (strcmp(cmd, req) == 0) {
            request_res(cmd_res, resource_count, customer_count, available, allocation, maximum);
        } else if (strcmp(cmd, rel) == 0) {
            release_res(cmd_res);
        } else if (strcmp(cmd, execute) == 0) {
            run();
        } else if (strcmp(cmd, star) == 0) {
            output_data();
        } else {
            printf("Invalid command!\nPlease enter RQ to request resources or RL to release resources\n");
        }
    }
}

int readFile(char* fileName) {  //, int* maximum[]) {
    FILE* in = fopen(fileName, "r");
    if (!in) {
        printf("Error in opening input file...exiting with error code -1\n");
        return -1;
    }

    //int int_test;
    const char delim[2] = ",";  // Add \n?
    char* token;

    char line[10];
    // Read file line by line
    while (fgets(line, sizeof(line), in)) {
        //printf("%s", line);
        // Read file char by char
        token = strtok(line, delim);
        while (token != NULL) {
            printf(" %s", token);
            token = strtok(NULL, delim);
        }
    }
    return 0;
}

/*
Requests Resources
Safety algorithm to decide if request is satisfied
Fills the allocation array, modifies need array?
*/
int request_res(int cmd_res[], int res_count, int proc_count, int available[], int allocation[][res_count], int maximum[][4]) {
    printf("Test resource request\n");
    return 1;
}

/*
Releases resources
*/
int release_res(int cmd_res[]) {
    printf("Test resource release\n");
    return 1;
}

void run() {
    printf("Run function here\n");
}

void output_data() {
    printf("Output data structures here\n");
}

int safety_algorithm(int res_count, int proc_count, int available[], int allocation[][res_count], int needl[res_count], int maximum[][4]) {
    int i, j, k;
    int f[proc_count], ans[proc_count], index = 0;
    int y = 0;

    for (k = 0; k < proc_count; k++) {
        f[k] = 0;
    }

    int need[proc_count][res_count];
    // Initialize need array
    for (i = 0; i < proc_count; i++) {
        for (j = 0; j < res_count; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    for (k = 0; k < 5; k++) {
        for (i = 0; i < proc_count; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (j = 0; j < res_count; j++) {
                    if (need[i][j] > available[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    ans[index++] = i;
                    for (y = 0; y < res_count; y++) {
                        available[y] += allocation[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    printf("Following is the SAFE Sequence\n");
    for (i = 0; i < proc_count - 1; i++)
        printf(" P%d ->", ans[i]);
    printf(" P%d", ans[proc_count - 1]);

    return (0);
}