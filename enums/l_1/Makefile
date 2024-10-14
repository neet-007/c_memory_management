# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
MUNIT_SRC = third_party/munit/munit.c  # Path to Munit source file

# Target binary
TARGET = main

# Build target
all: $(TARGET)

# Compile the main.c and Munit into the TARGET executable
$(TARGET): main.c $(MUNIT_SRC)
	$(CC) $(CFLAGS) -o $(TARGET) main.c $(MUNIT_SRC)

# Clean target (removes the executable)
clean:
	rm -f $(TARGET)

# Run target to run tests
run-tests: $(TARGET)
	./$(TARGET)

# PHONY ensures that these targets will run even if a file with the same name exists
.PHONY: all clean run-tests
