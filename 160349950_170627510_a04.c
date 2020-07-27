#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int request_res(int cmd_res[], int res_count, int proc_count, int available[], int allocation[][res_count], int need[][res_count], int maximum[][4]);
int release_res(int cmd_res[]);
void run();
void output_data();
int readFile(char* fileName, int maximum[][4]);  //, int* maximum[]);

int safety_algorithm(int res_count, int proc_count, int available[], int allocation[][res_count], int need[][res_count], int maximum[][4]);

int main(int argc, char* argv[]) {
    int resource_count = argc - 1;
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
            // TODO: Remove the following print statements eventually
            printf("%d", allocation[x][i]);
            printf("%d", need[x][i]);
        }
    }
    printf(" <-- Ignore this number\n");

    // Main function loop
    while (1) {
        // TODO: Fix entering single word commands
        printf("Enter Command: ");
        scanf("%s %d %d %d %d", cmd, &cmd_res[0], &cmd_res[1], &cmd_res[2], &cmd_res[3]);

        //printf("Entered Name: %s\n", cmd);
        //printf("%d\n", cmd_res[2]);

        if (strcmp(cmd, req) == 0) {
            request_res(cmd_res, resource_count, customer_count, available, allocation, need, maximum);
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

int readFile(char* fileName, int maximum[][4]) {  //, int* maximum[]) {
    FILE* in = fopen(fileName, "r");
    if (!in) {
        printf("Error in opening input file...exiting with error code -1\n");
        return -1;
    }
    const char* delim = ",\n\t ";
    char line[240];
    char* token;
    int i, n, j;
    i = 0;
    // Read file line by line
    while (fgets(line, sizeof(line), in)) {
        j = 1;
        // Initalize line tokens
        token = strtok(line, delim);
        // While not empty
        while (token != NULL) {
            n = atoi(token);
            maximum[i][j] = n;
            j++;
            printf(" %d", maximum[i][j]);
            token = strtok(NULL, delim);
        }
        // Use first array position to store the size
        maximum[i][0] = j;
        i++;
    }
    return 0;
}

/*
Requests Resources
Safety algorithm to decide if request is satisfied
Fills the allocation array, modifies need array?
*/
int request_res(int cmd_res[], int res_count, int proc_count, int available[], int allocation[][res_count], int need[][res_count], int maximum[][res_count]) {
    printf("Test resource request\n");
    // Create copy of allocation matrix, send that to safety algorithm
    // If correct, alter real allocation matrix
    int val = safety_algorithm(res_count, proc_count, available, allocation, need, maximum);
    if (val == 1) {
        printf("Failure\n");
        return 1;
    }
    return 0;
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

int safety_algorithm(int res_count, int proc_count, int available[], int allocation[][res_count], int need[][res_count], int maximum[][res_count]) {
    int i, j, k;
    int f[proc_count], ans[proc_count], index = 0;
    int y = 0;

    for (k = 0; k < proc_count; k++) {
        f[k] = 0;
    }

    // int need[proc_count][res_count];
    // Initialize need array
    for (i = 0; i < proc_count; i++) {
        for (j = 0; j < res_count; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    for (k = 0; k < proc_count; k++) {
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

    for (i = 0; i < proc_count; i++) {
        printf("f[%d] = %d\n", i, f[i]);
        if (f[i] == 0) {
            // printf("f[%d] = %d\n", i, f[i]);
            printf("Error: System not in a safe space\n");
            return 1;
        }
    }

    printf("Following is the safe sequence\n");
    for (i = 0; i < proc_count - 1; i++)
        printf(" Customer %d ->", ans[i]);
    printf(" Customer %d\n", ans[proc_count - 1]);

    return 0;
}