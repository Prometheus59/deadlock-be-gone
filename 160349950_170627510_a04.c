#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>


#define BUFFERSIZE 15
int request_res(int cmd_res[], int res_count, int proc_count, int available[], int allocation[][res_count], int need[][res_count], int maximum[][4]);
int release_res(int cmd_res[], int res_count, int proc_count, int available[], int allocation[][res_count], int need[][res_count], int maximum[][4]);  //TODO: May not need all of these params
void run_thread(int thread_index, int res_count, int available[], int allocation[][res_count], int need[][res_count], int maximum[][res_count]);
void run(int res_count, int proc_count, int available[], int allocation[][res_count], int need[][res_count], int maximum[][res_count]);
void output_data(int res_count, int proc_count, int available[], int allocation[][res_count], int need[][res_count], int maximum[][res_count]);
int read_file(char* fileName, int maximum[][4]);
int safety_algorithm(int res_count, int proc_count, int available[], int allocation[][res_count], int need[][res_count], int maximum[][4], int sequence[]);

sem_t semaphore;

typedef struct thread
{
    int thread_index;
    pthread_t handle;
} Thread;

int main(int argc, char* argv[]) {
    int resource_count = argc - 1;
    int customer_count = 5;
    printf("Resource count is %d\n", resource_count);
    printf("Number of Customers: %d\n", customer_count);

    // User input storage
    char cmd[3];
    int cmd_res[4];
    // Command Strings
    char req[] = "RQ";
    char rel[] = "RL";
    char execute[] = "Run";
    char star[] = "*";

    // initialize semaphore
    sem_init(&semaphore, 0, 1);

    int available[resource_count];
    int maximum[customer_count][resource_count];
    read_file("sample4_in.txt", maximum);
    //read_file("test_input.txt", maximum);

    int allocation[customer_count][resource_count];
    int need[customer_count][resource_count];

    printf("Currently Available Resources: ");
    // Initialize Data from command line & print
    for (int x = 0; x < resource_count; x++) {
        int num = strtol(argv[x + 1], NULL, 10);
        available[x] = num;
        printf(" %d", available[x]);
    }

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
        }
    }

    // Main function loop
    while (1) {
        // TODO: Find out why a command is sometimes printed x2 w/ last digit of first command == cmd (ex. RQ 0 10 10 10 10)
        printf("\nEnter Command: ");
        char buffer[BUFFERSIZE];
        fgets(buffer, BUFFERSIZE, stdin);
        // printf("%s", buffer);
        const char* token;
        const char* delim = "\n\t ";
        int i = 0;
        token = strtok(buffer, delim);
        strcpy(cmd, token);
        while (token != NULL) {
            if (i == 0) {
                token = strtok(NULL, delim);
                i++;
                continue;
            } else {
                cmd_res[i - 1] = atoi(token);
                //printf("cmd_res[i] for i=%d is %d\n", i - 1, cmd_res[i - 1]);
                token = strtok(NULL, delim);
                i++;
            }
        }

        if (strcmp(cmd, req) == 0) {
            request_res(cmd_res, resource_count, customer_count, available, allocation, need, maximum);
        } else if (strcmp(cmd, rel) == 0) {
            release_res(cmd_res, resource_count, customer_count, available, allocation, need, maximum);
        } else if (strcmp(cmd, execute) == 0) {
            run(resource_count, customer_count, available, allocation, need, maximum);
        } else if (strcmp(cmd, star) == 0) {
            output_data(resource_count, customer_count, available, allocation, need, maximum);
        } else {
            printf("Invalid command: %s\nPlease enter RQ to request resources or RL to release resources\n", cmd);
        }
    }
}

int read_file(char* fileName, int maximum[][4]) {
    FILE* in = fopen(fileName, "r");
    if (!in) {
        printf("Error in opening input file...exiting with error code -1\n");
        return -1;
    }
    const char* delim = ",\n\t ";
    char line[20];
    char* token;
    int i, n, j;
    i = 0;
    // Read file line by line
    while (fgets(line, sizeof(line), in)) {
        j = 0;
        // Initalize line tokens
        token = strtok(line, delim);
        while (token != NULL) {
            n = atoi(token);
            maximum[i][j] = n;
            j++;
            token = strtok(NULL, delim);
        }
        i++;
    }
    return 0;
}

/*
Requests Resources
Safety algorithm to decide if request is satisfied
Fills the allocation array, modifies need
*/
int request_res(int cmd_res[], int res_count, int proc_count, int available[], int allocation[][res_count], int need[][res_count], int maximum[][res_count]) {
    int thread = cmd_res[0];
    if (thread > proc_count){
        printf("Thread/Customer out of range\n");
        return 1;
    }
    int request[res_count];
    int r;
    // Create request array
    //printf("Request Array for thread %d\n", thread);
    for (r = 1; r <= res_count; r++) {
        request[r - 1] = cmd_res[r];
        //printf("%d ", request[r - 1]);
    }
    // Check if request > required
    for (r = 0; r < res_count; r++) {
        if (request[r] > need[thread][r]) {
            printf("Error: Process has exceeded its maximum claim\n");
            return 1;
        }
    }
    // Check if request > available resources
    for (r = 0; r < res_count; r++) {
        if (request[r] > available[r]) {
            printf("Error: Process must wait, resources not available\n");
            return 1;
        }
    }

    // Pretend allocate resources to customer/thread

    // Make copy arrays
    int available_copy[res_count];
    int allocation_copy[proc_count][res_count];
    int need_copy[proc_count][res_count];
    int maximum_copy[proc_count][res_count];
    // Populate arrays
    for (int p = 0; p < proc_count; p++) {
        for (r = 0; r < res_count; r++) {
            allocation_copy[p][r] = allocation[p][r];
            need_copy[p][r] = need[p][r];
            maximum_copy[p][r] = maximum[p][r];
            if (p == 0) {
                available_copy[r] = available[r];
            }
        }
    }

    // Pretend-allocate resources
    for (r = 0; r < res_count; r++) {
        available_copy[r] = available_copy[r] - request[r];
        allocation_copy[thread][r] = allocation_copy[thread][r] + request[r];
        need_copy[thread][r] = need_copy[thread][r] - request[r];
    }

    int sequence[proc_count];
    int val = safety_algorithm(res_count, proc_count, available_copy, allocation_copy, need_copy, maximum_copy, sequence);

    if (val == 1) {
        // Bad request
        printf("Request not satisfied\n");

        // TESTING
        // printf("For copy:\n");
        // output_data(res_count, proc_count, available_copy, allocation_copy, need_copy, maximum_copy);
        // printf("\nFor realsies:\n");
        // output_data(res_count, proc_count, available, allocation, need, maximum);

    } else {
        printf("Request is satisfied\n");
        for (r = 0; r < res_count; r++) {
            available[r] = available[r] - request[r];
            allocation[thread][r] = allocation[thread][r] + request[r];
            need[thread][r] = need[thread][r] - request[r];
        }
        safety_algorithm(res_count, proc_count, available, allocation, need, maximum, sequence);
        // printf("Following is the safe sequence\n");
        // for (int i = 0; i < proc_count - 1; i++) {
        //     printf(" Customer %d ->", sequence[i]);
        // }
        // printf(" Customer %d\n", sequence[proc_count - 1]);
        // output_data(res_count, proc_count, available, allocation, need, maximum);
    }
    return 0;
}

/*
Releases resources
*/
int release_res(int cmd_res[], int res_count, int proc_count, int available[], int allocation[][res_count], int need[][res_count], int maximum[][res_count]) {
    printf("Test resource release\n");
    int thread = cmd_res[0];
    if (thread > proc_count){
        printf("Thread/Customer out of range\n");
        return 1;
    }
    int release[res_count];
    int r;
    
    // Create release array
    for (r=1; r<=res_count; r++){
        release[r-1] = cmd_res[r];
    }

    // Check if release > allocated
    for (r = 0; r < res_count; r++){
        if (release[r] > allocation[thread][r]){
            printf("Error: Cannot release more resources than currently allocated\n");
            return 1;
        }
    }

    // Release resources
    for (r = 0; r < res_count; r++){
        allocation[thread][r] -= release[r];
        available[r] = available[r] + release[r];
        need[thread][r] += release[r];
    }
    return 0;
}

/*
Runs all threads, if safe sequence possible
*/
void run(int res_count, int proc_count, int available[], int allocation[][res_count], int need[][res_count], int maximum[][res_count]) {
    printf("Run functionn here\n");
    // Run safety algorithm to get sequence
    int sequence[proc_count];
    int val = safety_algorithm(res_count, proc_count, available, allocation, need, maximum, sequence);
    if (val == 0) {
        printf("Safe Sequence is: ");
        for (int j = 0; j < proc_count; j++) {
            printf("%d ", sequence[j]);
        }
        printf("\nNow going to execute the threads:\n\n");
        // Run each thread in order.
        for (int x = 0; x < proc_count; x++) {
            run_thread(sequence[x], res_count, available, allocation, need, maximum);
        }
    } else {
        printf("\nError: Cannot run threads right now\n");
    }
}

/*
  Outputs Available resources, maximum resources, allocation, and resources needed
*/
void output_data(int res_count, int proc_count, int available[], int allocation[][res_count], int need[][res_count], int maximum[][res_count]) {
    printf("Available Resources: ");
    for (int x = 0; x < res_count; x++) {
        printf(" %d", available[x]);
    }
    printf("\n\nMaximum Resources: \n");
    for (int x = 0; x < proc_count; x++) {
        for (int i = 0; i < res_count; i++) {
            printf("%d", maximum[x][i]);
            if (i + 1 < res_count) printf(",");
        }
        printf("\n");
    }
    printf("\nAllocation: \n");
    for (int x = 0; x < proc_count; x++) {
        for (int i = 0; i < res_count; i++) {
            printf("%d ", allocation[x][i]);
        }
        printf("\n");
    }
    printf("\nNeed: \n");
    for (int x = 0; x < proc_count; x++) {
        for (int i = 0; i < res_count; i++) {
            printf("%d ", need[x][i]);
        }
        printf("\n");
    }
}

/*
Runs a thread, specified by thread_index
*/
void run_thread(int thread_index, int res_count, int available[], int allocation[][res_count], int need[][res_count], int maximum[][res_count]) {
    int r;
    printf("\n\n--> Customer/Thread %d\n", thread_index);
    printf("        Allocated Resources: ");
    for (r = 0; r < res_count; r++) {
        printf(" %d", allocation[thread_index][r]);
    }
    printf("\n        Needed: ");
    for (r = 0; r < res_count; r++) {
        printf(" %d", need[thread_index][r]);
        need[thread_index][r] = 0;
    }

    sem_wait(&semaphore);
    printf("\n        Thread has started");
    sem_post(&semaphore);
    printf("\n        Thread has finished\n");
    printf("        Thread is releasing resources\n");

    // TODO: Create and add relevant values to a cmd_res[] for release_res()
    // release_res();
    
    printf("        Now available:");
    for (r = 0; r < res_count; r++) {
        available[r] = available[r] + allocation[thread_index][r];
        allocation[thread_index][r] = 0;
        printf(" %d", available[r]);
    }
    return;
}

/*
Algorithm to determine whether state is safe
*/
// TODO: Change this algorithm?
int safety_algorithm(int res_count, int proc_count, int available[], int allocation[][res_count], int need[][res_count], int maximum[][res_count], int sequence[]) {
    int index = 0;
    int k, i, j, y;
    // Create a temporary available array so as not to screw everything up
    int temp_avail[res_count];
    for (i = 0; i < res_count; i++){
        temp_avail[i] = available[i];
    }
    int f[proc_count], ans[proc_count];
    for (k = 0; k < proc_count; k++) {
        f[k] = 0;
    }

    for (k = 0; k < proc_count; k++) {
        for (i = 0; i < proc_count; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (j = 0; j < res_count; j++) {
                    if (need[i][j] > temp_avail[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    ans[index++] = i;
                    for (y = 0; y < res_count; y++) {
                            temp_avail[y] += allocation[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    for (i = 0; i < proc_count; i++) {
        if (f[i] == 0) {
            printf("Error: System not in a safe space\n");
            return 1;
        }
    }

    for (i = 0; i < proc_count - 1; i++) {
        sequence[i] = ans[i];
    }
    sequence[proc_count - 1] = ans[proc_count - 1];

    return 0;
}