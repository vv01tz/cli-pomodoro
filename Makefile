CC=gcc

all: timer

timer: timer.c
	$(CC) -o timer timer.c

clean:
	rm timer
