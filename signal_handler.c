/**
 * @file signal_handler.c
 * @brief Sets a signal handler for SIGINT, the handler prints a message and then quits
 */

/**
 * Modified by: Nick Bergst
 * 
 * Brief summary of modifications: gracefully ends in main instead of in signal handler
 */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int signal_empty;

/**
 * @brief Signal handler for SIGINT - prints a message
 */
void handle_signalInt() {
    printf("Received a signal\n");
    //signal no longer not yet recieved
    signal_empty = 0;
}

int main() {

    //have not recieved a signal yet
    signal_empty = 1;

    // Register for the signal
    signal(SIGINT, handle_signalInt);

    // Wait until a signal is received
    while(signal_empty) {
        printf("Sleeping\n");
        sleep(1);
    }

    return 0;
}