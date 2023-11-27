# Makefile for compiling multiple C source files into a shared library

# Compiler
CC := gcc

# Compiler flags
CFLAGS := -I/home/admin/frr-9.0.1 -I/home/admin/frr-9.0.1/lib -I/home/admin/frr-9.0.1/zebra -Wall -fPIC -g -O0

# Source files
SRCS := $(wildcard *.c)

# Object files
OBJS := $(SRCS:.c=.o)

# Output library name
OUTPUT := dp_ebang_plugin.so

# Default rule
all: $(OUTPUT)

# Rule to generate object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to generate shared library
$(OUTPUT): $(OBJS)
	$(CC) -shared $(OBJS) -o $(OUTPUT)

# Clean rule
clean:
	rm -f $(OBJS) $(OUTPUT)