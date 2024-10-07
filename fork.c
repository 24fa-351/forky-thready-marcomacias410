#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h> 

void pattern_1(int num) {
    int status;
    pid_t pids[num];
    for (int i = 0; i < num; ++i) {
        pid_t pid = fork();

        if (pid == 0) {
            srand(getpid());
            int random = rand() % 8 + 1;

            printf("Process %d (%d) beginning... sleeping for %d seconds\n", i,
                   getpid(), random);
            sleep(random);

            printf("Process %d (%d) exiting  \n", i, getpid());

            exit(0);
        } else {
            pids[i] = pid;
        }
    }

    for (int i = 0; i < num; ++i) {
        waitpid(pids[i], &status, 0);
    }
}

void pattern_2(int num) {
    pid_t pids_arr[num];
    pid_t pid;
    int status;

    int pids_id[num];

    for (int i = 0; i < num; ++i) {
        if (i == 0) pid = fork();

        if (pid == 0) {
            srand(getpid());
            int random = rand() % 8 + 1;

            sleep(1);
            printf("Process %d (%d) beginning... sleeping for %d seconds\n",
                   i + 1, getpid(), random);

            sleep(random);

            printf("Process %d created Process %d \n", getppid(), getpid());

            sleep(1);
            printf("Process %d (%d) exiting \n", i + 1, getpid());

            pid = fork();

        } else {
            waitpid(pid, &status, 0);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s [123] <num>\n", argv[0]);
        return 1;
    }

    if (argv[1][0] != '1' && argv[1][0] != '2' && argv[1][0] != '3') {
        printf("Invalid pattern number. Gotta be 1/2/3\n");
        return 1;
    }
    // int pattern_num = atoi(argv[2]);
    int pattern_num = argv[1][0] - '0';

    //  int num_of_processes = atoi(argv[1]);
    int num_of_processes;
    if (0 == sscanf(argv[2], "%d", &num_of_processes) || num_of_processes < 1) {
        printf("Invalid number of processes (1+)\n");
        return 1;
    }

    if (pattern_num == 1 && num_of_processes >= 1 && num_of_processes <= 256)
        pattern_1(num_of_processes);
    if (pattern_num == 2 && num_of_processes >= 1 && num_of_processes <= 256)
        pattern_2(num_of_processes);

    return 0;
}