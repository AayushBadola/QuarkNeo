# Makefile for the Quark library

CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c11
AR = ar
ARFLAGS = rcs

# Target library
LIB = libquark.a

# Source files
SRCS = quark.c
OBJS = $(SRCS:.c=.o)

# Header files
HDRS = quark.h

# Default target
all: $(LIB)

# Rule to build the library
$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

# Rule to build object files
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Example program
example: example.o $(LIB)
	$(CC) $(CFLAGS) -o $@ $^ -L. -lquark

# Clean up generated files
clean:
	rm -f $(OBJS) $(LIB) example example.o

# Install the library and header files
install: $(LIB) $(HDRS)
	mkdir -p $(DESTDIR)/usr/local/lib
	mkdir -p $(DESTDIR)/usr/local/include
	cp $(LIB) $(DESTDIR)/usr/local/lib/
	cp $(HDRS) $(DESTDIR)/usr/local/include/

.PHONY: all clean install
