/**
 * File: send_signal
 * Modified by: Nicholas Bergst
 * 
 * Brief summary of program: sends a psuedo-random number 
 */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[]) {
    // if there's a command line arg, convert it to a pid
    if (argc > 1) {
        pid_t myPid;
        sscanf(argv[1], "%d", &myPid);
        // generate psuedo-random number based on current time, and store it
        union sigval toSend;
        srand(clock());
        toSend.sival_int = rand();
        // send it
        sigqueue(myPid, SIGUSR1, toSend);
    } else {
        printf("Please provide a Process ID!");
    }
    return 0;
}
