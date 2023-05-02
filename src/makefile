.PHONY: all clean

EXECUTABLE = c23

INCLUDES = -I.

SRCDIR = .
OBJDIR = obj
BINDIR = bin

SOURCES = main.c
OBJS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o) )

CC = gcc-13
CFLAGS =\
	-c\
	-std=c2x\
	-Wall\
	-Wextra\
	-Wpedantic\
	-fsanitize=undefined\
	-fsanitize-undefined-trap-on-error\
	-O0\
	-g3

LD = gcc-13
LDFLAGS =\
	-fsanitize=undefined\
	-fsanitize-undefined-trap-on-error

all: $(BINDIR)/$(EXECUTABLE)

$(OBJDIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(BINDIR)/$(EXECUTABLE): $(OBJS)
	mkdir -p $(BINDIR)
	$(LD) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(OBJS) $(BINDIR)/$(EXECUTABLE)
