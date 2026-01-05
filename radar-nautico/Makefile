CC=gcc
CFLAGS=-Wall -Wextra -g -Wvla -Wpedantic -Wdeclaration-after-statement
LDFLAGS=-lm

SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

radar: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

clean:
	rm -f src/*.o radar

test: radar
	bash tests/test_smoke.sh
