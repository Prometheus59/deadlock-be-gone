#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Get from user input

int request_res();
int release_res();
int safety_algorithm();

int main(int argc, char* argv[]) {
    int resource_count = argc - 1;
    // int customer_count = 5;

    int available[resource_count];
    for (int x = 0; x < resource_count; x++) {
        int num = strtol(argv[x + 1], NULL, 10);
        available[x] = num;
    }
    for (int x = 0; x < resource_count; x++) {
        printf("%d\n", available[x]);
    }
    // int max[customer_count][resource_count];
    // int allocation[customer_count][resource_count];
    // int need[customer_count][resource_count];
}