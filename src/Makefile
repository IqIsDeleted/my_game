CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
LFLAGS = -lncurses
SOURCES = minesweeper.c
EXECUTABLE = minesweeper

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE)