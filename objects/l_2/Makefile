# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude  # Include the directory where exercise.h is located
MUNIT_SRC = third_party/munit/munit.c  # Path to Munit source file
TARGET = main
SRC_FILES = main.c snekobject.c $(MUNIT_SRC)  # Add exercise.c as a source file

# Build target
all: $(TARGET)

# Compile the source files (main.c, exercise.c, munit.c) into the TARGET executable
$(TARGET): $(SRC_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC_FILES)

# Clean target (removes the executable)
clean:
	rm -f $(TARGET)

# Run the tests
run-tests: $(TARGET)
	./$(TARGET)

# PHONY ensures that these targets will run even if a file with the same name exists
.PHONY: all clean run-tests
