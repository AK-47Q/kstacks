CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iheaders

all: libkstacks.a

libkstacks.a: codes/kstacks.o
	ar rcs $@ $^

codes/kstacks.o: codes/kstacks.c headers/kstacks.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f codes/*.o libkstacks.a

.PHONY: all clean
