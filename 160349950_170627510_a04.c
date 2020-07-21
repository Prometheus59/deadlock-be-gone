#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int request_res();
int release_res();
int safety_algorithm();
int read_file();

int main(int argc, char* argv[]) {
    int resource_count = argc - 1;
    int customer_count = 5;
    int available[resource_count];
    // int max[customer_count][resource_count] = {
    int max[][4] = {
        {6, 4, 7, 3}, {4, 2, 3, 2}, {2, 5, 3, 3}, {6, 3, 3, 2}, {5, 6, 7, 5}};
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
    printf("\nMaximum resources from file:\n");
    for (int x = 0; x < customer_count; x++) {
        for (int i = 0; i < resource_count; i++) {
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

