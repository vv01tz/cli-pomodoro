CC=gcc

all: timer

timer: timer.c
	$(CC) -o timer.o timer.c

clean:
	rm -iv *.o
