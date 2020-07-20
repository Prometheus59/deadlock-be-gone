#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Get from user input

int request_res();
int release_res();
int safety_algorithm();

int main(int argc, char* argv[]) {
    int m = argc - 1;
    int n = 5;  // idk what this does

    int available[m];
    int max[n][m];
    int allocation[n][m];
    int need[n][m];
}