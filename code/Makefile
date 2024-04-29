CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS =

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE = $(BINDIR)/mon_programme

MAIN = $(SRCDIR)/main.c

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(shell mkdir -p $(OBJDIR) $(BINDIR))

clean:
    rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean