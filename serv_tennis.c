/**
 * File: serv_tennis
 * Modified by: Nicholas Bergst
 * 
 * Brief summary of program: serves a 'ball' signal
 */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int playing;

/**
 * @brief Signal handler for SIGUSR1 - does ball stuff
 */
void handle_signalUsr1(int sig, siginfo_t *info, void *ucontext) {
    if (sig == SIGUSR1) {
        int recScore = info->si_value.sival_int % 10;
        int serScore = (info->si_value.sival_int / 10) % 10;
        int bounceA = (info->si_value.sival_int / 100) % 10;
        int bounceB = (info->si_value.sival_int / 1000) % 10;
        int meScord = (info->si_value.sival_int / 10000) % 10;
        playing = (info->si_value.sival_int / 100000) % 10;
        int otrScrd;
        if (playing) {
            if (meScord) {
                printf("Server Scored, ");
                if (recScore == serScore) {
                    if (recScore == 3) {
                        printf("Duece ");
                    } else if (recScore == 0) {
                        printf("Love ");
                    } else {
                        printf("%d ", recScore * 15);
                    }
                    printf("All\n");
                } else {
                    if (serScore == 3) {
                        printf("Duece-");
                    } else if (serScore == 0) {
                        printf("Love-");
                    } else if (serScore == 4) {
                        printf("Ad-Out-");
                    } else {
                        printf("%d-", serScore * 15);
                    }
                    if (recScore == 3) {
                        printf("Duece\n");
                    } else if (recScore == 0) {
                        printf("Love\n");
                    } else if (recScore == 4) {
                        printf("Ad-Out\n");
                    } else {
                        printf("%d\n", recScore * 15);
                    }
                }
                if (recScore == 4) {
                    printf("Server wins\a\a\a\a\a\n");
                    playing = 0;
                }
            } else {
                srand(clock());
                if (bounceA == rand() % 4 || bounceB == rand() % 4) {
                    otrScrd = 0;
                    bounceA = rand() % 4;
                    bounceB = rand() % 4;
                    printf("Server Returns\a\n");
                } else {
                    otrScrd = 1;
                    serScore++;
                    printf("Reciever Scores\a\a\a\n");
                }
            }
        }
        union sigval ball;
        ball.sival_int = recScore + (serScore * 10) + (bounceA * 100) + (bounceB * 1000) + (otrScrd * 10000) + (playing * 100000);
        sleep(((rand() % 1000) / 100) + 1);
        sigqueue(info->si_pid, SIGUSR1, ball);
    }
}

int main(int argc, char* argv[]) {
    // if there's a command line arg, convert it to a pid
    if (argc > 1) {
        pid_t myPid;
        sscanf(argv[1], "%d", &myPid);
        union sigval toSend;
        srand(clock());
        toSend.sival_int = 0 + (0 * 10) + ((rand() % 4) * 100) + ((rand() % 4) * 1000) + (0 * 10000) + (playing * 100000);
        // send it
        sigqueue(myPid, SIGUSR1, toSend);
        
        // Register for the signal
        struct sigaction toDo;
        struct sigaction Did;
        toDo.sa_sigaction = handle_signalUsr1;
        toDo.sa_flags = SA_SIGINFO;
        sigaction(SIGUSR1, &toDo, &Did);

        // Wait until a signal is received
        while(playing) {
            sleep(1);
        }
    } else {
        printf("Please provide a Process ID!\n");
    }
    return 0;
}