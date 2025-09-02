CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
TARGET = shell
OBJDIR = obj
SRCDIR = .

SOURCES = main.c builtins.c parser.c
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
