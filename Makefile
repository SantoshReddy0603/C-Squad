# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra -g

# Source Files
SRCS = main.c admin.c employee.c

# Object Files
OBJS = $(SRCS:.c=.o)

# Header Files
HEADERS = admin.h employee.h common.h

# Output Executable
TARGET = ems

# Default Target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# PHONY targets (not actual files)
.PHONY: all clean run
