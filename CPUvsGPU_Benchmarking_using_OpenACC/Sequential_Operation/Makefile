# Compiler and compile options.
CC = gcc
CFLAGS = -Wall -O2 -g

# Linking flags - you might need to adjust based on where LAPACK and BLAS are on your system
LDFLAGS = -llapacke -lblas -lm

# Source files
SRCS = add_matrix.c \
       multiply_matrix.c \
       sub_matrix.c \
       div_matrix.c \
       random_matrix.c \
       sequential_main.c \
       transpose_matrix.c \
	   n_power_matrix.c \
       rotate_matrix.c\
	   matrixSize.h 

# Object files
OBJS = $(SRCS: .h, .c=.o)

# Output executable name
OUT = calculator

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(OUT) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OUT)

