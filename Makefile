# Makefile for forky_thread.exe

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra

# Executable name and source files
TARGET = forky_thread.exe
SRCS = forky_thread.c

# Build the executable
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

# Clean up generated files
clean:
	del $(TARGET)
