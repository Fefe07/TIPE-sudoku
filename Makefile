all: main
	./main
	
CC = gcc
CFLAGS = -lm -g -pg -fsanitize=address -O2

SRCS = $(wildcard *.c)
HEADERS = $(wildcard *.h)

main: $(SRCS) 
	$(CC) $(CFLAGS) $(SRCS) -o "$@" -g
main-debug: $(SRCS) 
	$(CC) $(CFLAGS) -O0 $(SRCS) -o "$@"

clean:
	rm -f main main-debug

