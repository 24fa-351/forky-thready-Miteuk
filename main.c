#include "forky.h"

int main(int argc, char *argv[]) {

    int num_processes = atoi(argv[1]);
    int pattern_number = atoi(argv[2]);

    if (num_processes < 1 || num_processes > 256) {
        fprintf(stderr, "Number of processes must be between 1 and 256.\n");
        return 1;
    }

    if (pattern_number == 1) {
        pattern1(num_processes); 
    } else if (pattern_number == 2) {
        pattern2(num_processes); 
    } else {
        perror("Invalid pattern number. Must be 1, 2, or 3.\n");
    }

    return 0;
}