/**
 * File: recv_signal.c
 * Modified by: Nicholas Bergst
 * 
 * Brief summary of program: sits in a loop until a SIGUSR1 signal is recieved, prints the sent number.
 */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int signal_empty;

/**
 * @brief Signal handler for SIGUSR1 - prints a message
 */
void handle_signalUsr1(int sig, siginfo_t *info, void *ucontext) {
    printf("Received a signal\n");
    //signal no longer not yet recieved
    signal_empty = 0;
    //print pid
    if (sig == SIGUSR1) {
        printf("Sent Number: %d\n", info->si_value.sival_int);
    }
}

int main() {

    //have not recieved a signal yet
    signal_empty = 1;

    // Register for the signal
    struct sigaction toDo;
    struct sigaction Did;
    toDo.sa_sigaction = handle_signalUsr1;
    toDo.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &toDo, &Did);

    // Wait until a signal is received
    while(signal_empty) {
        sleep(1);
    }

    return 0;
}