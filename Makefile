
CC = gcc
CFLAGS = 

all: server client

server: p1-serECO.c p1-tTCP.c
	$(CC) $(CFLAGS) -o server p1-serECO.c p1-tTCP.c

client: p1-cliECO.c p1-tTCP.c
	$(CC) $(CFLAGS) -o client p1-cliECO.c p1-tTCP.c

clean:
	rm -f client server

.PHONY: all clean

