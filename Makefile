CFLAGS=-c -g -Wall -Werror
CC=gcc

all: signal_handler signal_alarm signal_segfault signal_sigaction recv_signal send_signal  recv_tennis serv_tennis

signal_handler: signal_handler.o
	$(CC) -o signal_handler signal_handler.o

signal_alarm: signal_alarm.o
	$(CC) -o signal_alarm signal_alarm.o

signal_segfault: signal_segfault.o
	$(CC) -o signal_segfault signal_segfault.o

signal_sigaction: signal_sigaction.o
	$(CC) -o signal_sigaction signal_sigaction.o

recv_signal: recv_signal.o
	$(CC) -o recv_signal recv_signal.o

send_signal: send_signal.o
	$(CC) -o send_signal send_signal.o

recv_tennis: recv_tennis.o
	$(CC) -o recv_tennis recv_tennis.o

serv_tennis: serv_tennis.o
	$(CC) -o serv_tennis serv_tennis.o

clean:
	rm -f *.o signal_handler signal_alarm signal_segfault signal_sigaction recv_signal send_signal recv_tennis serv_tennis

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<