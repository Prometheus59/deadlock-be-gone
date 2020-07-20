#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Get from user input
int m = 5;
int n = 5;

int available[m];
int max[n][m];
int allocation[n][m];
int need[n][m];

int request_res();
int release_res();
int safety_algorithm();
