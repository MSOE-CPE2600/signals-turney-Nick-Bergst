/**
 * File: signal_alarm.c
 * Modified by: Nicholas Bergst
 * 
 * Brief summary of program: Sets a 5 second alarm, and recieves its signal
 */
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int signal_empty;

/**
 * @brief Signal handler for SIGALRM - prints a message
 */
void handle_signalAlrm() {
    printf("Received a signal\n");
    //signal no longer not yet recieved
    signal_empty = 0;
}

int main() {

    //have not recieved a signal yet
    signal_empty = 1;

    // Register for the signal
    signal(SIGALRM, handle_signalAlrm);

    //set a 5 second alarm
    alarm(5);

    // Wait until a signal is received
    while(signal_empty) {
        printf("Sleeping\n");
        sleep(1);
    }

    return 0;
}
