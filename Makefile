
CC = gcc
CFLAGS = 

all: server client

server: p1-serECO.c p1-tTCP.c
	$(CC) $(CFLAGS) -o server-eco p1-serECO.c p1-tTCP.c

client: p1-cliECO.c p1-tTCP.c
	$(CC) $(CFLAGS) -o client-eco p1-cliECO.c p1-tTCP.c

clean:
	rm -f client-eco server-eco

.PHONY: all clean

