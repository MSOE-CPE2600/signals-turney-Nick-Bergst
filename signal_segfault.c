/**
 * @file signal_segfault.c
 * @brief Program that dereferences a null pointer causing a segmentation fault
 */

/**
 * Modified by: Nicholas Bergst
 * 
 * Brief summary of modifications: Catches a segfault
 */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Signal handler for SIGSEGV - prints a message.
 */
void handle_signalSegV() {
    printf("Received a signal\n");
    //signal recieved, I just really don't like dealing with the endless loop
    exit(1);
}

int main (int argc, char* argv[]) {
    // Declare a null pointer
    int* i = NULL;

    //prepare to catch segfault
    signal(SIGSEGV, handle_signalSegV);
    
    // Dereference the null pointer if you haven't already
    printf("The value of i is: %d\n", *i);

    // Return to exit the program
    return 0;
}