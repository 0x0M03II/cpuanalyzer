# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Iinclude/platform -Wall -Wextra
LDFLAGS = -o $(BINDIR)/$(EXE)

# Define directories
SRCDIR = src
OBJDIR = build/obj
BINDIR = build/bin
LIBDIR = build/lib
INCLUDEDIR = include

# Define source files and object files
SRCS = $(wildcard $(SRCDIR)/common/**/*.c) $(wildcard $(SRCDIR)/platform/**/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Define the target executable
EXE = cpu_profiler.exe

# Default target
all: $(BINDIR)/$(EXE)

# Rule for building the executable
$(BINDIR)/$(EXE): $(OBJS)
	@mkdir -p $(BINDIR) $(OBJDIR)
	$(CC) $(LDFLAGS) $(OBJS)

# Rule for compiling source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for building assembly files
$(OBJDIR)/%.o: $(SRCDIR)/%.S
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJDIR)/**/*/*.o
	rm -f $(BINDIR)\$(EXE)

# Phony targets
.PHONY: all clean
