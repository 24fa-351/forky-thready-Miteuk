#include "forky.h"

//Main -> 1,2,3,4,5,6,7
void pattern1(int num_processes) {

 srand(time(NULL));  // Seed for random sleep times
    printf("** Pattern 1: creating %d processes\n", num_processes);
    
    for (int ix = 0; ix < num_processes; ix++) {
        pid_t pid = fork();
        int sleep_time = rand() % 8 + 1;  
        if (pid == 0) { 
            printf("Process %d (pid %d) created: will sleep for %d seconds\n", ix, getpid(), sleep_time);
            sleep(sleep_time); 
            printf("Process %d (pid %d): exiting\n", ix, getpid());
            exit(0);  
        } else if (pid > 0) {  
            printf("Parent: created child %d (pid %d)\n", ix, pid);
        } else {
            perror("fork");
            exit(1);
        }
    }
 
    printf("** Pattern 1: All processes created\n");

    for (int i = 0; i < num_processes; i++) {
        wait(NULL); 
    }

    printf("** Pattern 1: All children have exited\n");
}


//Main -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7
void pattern2(int num_processes) {
    srand(time(NULL)); 
    printf("** Pattern 2: creating %d processes\n", num_processes);
    
    pid_t pid = fork();
    if (pid == 0) { 
        int sleep_time = rand() % 8 + 1;  
        for (int i = 0; i < num_processes; i++) {
            pid_t child_pid = fork();
            sleep_time = rand() % 8 + 1;
            if (child_pid == 0) {  
                printf("Child %d (pid %d): starting\n", i, getpid());
                printf("Child %d (pid %d), sleeping %d seconds after creating child %d\n", i, getppid(), sleep_time, i);
            } else if (child_pid > 0) {
                sleep(sleep_time);  
                printf("Child %d (pid %d), waiting for child %d (pid %d)\n", i, getpid(), i, child_pid);
                wait(NULL);  
                printf("Child %d (pid %d) exiting.\n", i, getpid());
                exit(0);
            } else {
                perror("fork");
                exit(1);
            }
        }
        printf("Child %d (pid %d) [no children created] sleeping %d seconds\n", num_processes, getpid(), sleep_time);
        sleep(sleep_time);
        printf("Child %d (pid %d) exiting.\n", num_processes, getpid());
        exit(0);
    } else if (pid > 0) {  
        printf("Parent: created child 0 (pid %d)\n", pid);
        wait(NULL);  
        printf("Parent: child 0 (pid %d) has exited\n", pid);
        printf("** Pattern 2: All children have exited\n");
    } else {
        perror("fork");
        exit(1);
    }
}