CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SOURCES = main.c third_party/munit/munit.c http.c # Include other source files as needed
OBJECTS = $(SOURCES:.c=.o)

all: main

main: $(OBJECTS)
	$(CC) -o $@ $^

clean:
	rm -f main $(OBJECTS)
