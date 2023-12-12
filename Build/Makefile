CC = gcc
CPP = g++
CFLAGS = -Wall -Wextra

all: Robot_pi

Robot_pi: main.o utils.o
    $(CC) $(CFLAGS) -DDEFINE_VALUE=42 -o myprogram main.o utils.o

main.o: main.c
    $(CC) $(CFLAGS) -c main.c

utils.o: utils.c
    $(CC) $(CFLAGS) -c utils.c

clean:
    rm -f myprogram *.o