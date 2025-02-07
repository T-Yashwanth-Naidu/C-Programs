# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra -pthread

# Target Executable
TARGET = aeb_simulation

# Source Files
SRCS = main.c sensors.c aeb_system.c input_handler.c

# Object Files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lpthread

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJS) $(TARGET)
